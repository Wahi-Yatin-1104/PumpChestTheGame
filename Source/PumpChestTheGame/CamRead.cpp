// Fill out your copyright notice in the Description page of Project Settings.


#include "CamRead.h"

// Sets default values
ACamRead::ACamRead(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    rootComp = CreateDefaultSubobject<USceneComponent>("Root");
    Screen_Raw = CreateDefaultSubobject<UStaticMeshComponent>("Screen Raw");
    Screen_Post = CreateDefaultSubobject<UStaticMeshComponent>("Screen Post");

    Brightness = 0;
    Multiply = 1;

    // Initialize OpenCV and webcam properties
    CameraID = 0;
    VideoTrackID = 0;
    isStreamOpen = false;
    VideoSize = FVector2D(1920, 1080);
    RefreshRate = 30.0f;

}

// Called when the game starts or when spawned
void ACamRead::BeginPlay()
{
	Super::BeginPlay();

    isStreamOpen = true;
    // Prepare the color data array
    ColorData.AddDefaulted(VideoSize.X * VideoSize.Y);
    // setup openCV
    cvSize = cv::Size(VideoSize.X, VideoSize.Y);
    cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());
    // create dynamic texture
    Camera_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);

#if WITH_EDITORONLY_DATA
    Camera_Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif
    Camera_Texture2D->SRGB = Camera_RenderTarget->SRGB;
}

// Called every frame
void ACamRead::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RefreshTimer += DeltaTime;
    if (isStreamOpen && RefreshTimer >= 1.0f / RefreshRate)
    {
        RefreshTimer -= 1.0f / RefreshRate;
        ReadFrame();
        OnNextVideoFrame();
    }

}
void ACamRead::UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData)
{
    if (Texture && Texture->GetResource())
    {
        struct FUpdateTextureRegionsData
        {
            FTexture2DResource* Texture2DResource;
            int32 MipIndex;
            uint32 NumRegions;
            FUpdateTextureRegion2D* Regions;
            uint32 SrcPitch;
            uint32 SrcBpp;
            uint8* SrcData;
            bool bFreeData;
        };

        FUpdateTextureRegionsData* RegionData = new FUpdateTextureRegionsData;

        RegionData->Texture2DResource = (FTexture2DResource*)Texture->GetResource();
        RegionData->MipIndex = MipIndex;
        RegionData->NumRegions = NumRegions;
        RegionData->Regions = Regions;
        RegionData->SrcPitch = SrcPitch;
        RegionData->SrcBpp = SrcBpp;
        RegionData->SrcData = SrcData;
        RegionData->bFreeData = bFreeData;

        ENQUEUE_RENDER_COMMAND(UpdateTextureRegionsData)(
            [RegionData](FRHICommandListImmediate& RHICmdList)
            {
                for (uint32 RegionIndex = 0; RegionIndex < RegionData->NumRegions; ++RegionIndex)
                {
                    int32 CurrentFirstMip = RegionData->Texture2DResource->GetCurrentFirstMip();
                    if (RegionData->MipIndex >= CurrentFirstMip)
                    {
                        RHIUpdateTexture2D(
                            RegionData->Texture2DResource->GetTexture2DRHI(),
                            RegionData->MipIndex - CurrentFirstMip,
                            RegionData->Regions[RegionIndex],
                            RegionData->SrcPitch,
                            RegionData->SrcData + RegionData->Regions[RegionIndex].SrcY * RegionData->SrcPitch + RegionData->Regions[RegionIndex].SrcX * RegionData->SrcBpp
                        );
                    }
                }
                if (RegionData->bFreeData)
                {
                    FMemory::Free(RegionData->SrcData);
                }
                delete RegionData;
            });
    }
}



bool ACamRead::ReadFrame()
{
    if (!Camera_Texture2D || !Camera_RenderTarget) return false;

    // Read the pixels from the RenderTarget and store them in a FColor array
    FRenderTarget* RenderTarget = Camera_RenderTarget->GameThread_GetRenderTargetResource();
    RenderTarget->ReadPixels(ColorData);

    // Get the color data
    cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());
    cvMat.convertTo(cvMat, -1, Multiply, Brightness);

    // Show the OpenCV window
    if (!cvMat.empty())
    {
        // cv::imshow("Display", cvMat);
    }

    // Update the texture regions
    FUpdateTextureRegion2D Region(0, 0, 0, 0, VideoSize.X, VideoSize.Y);
    UpdateTextureRegions(Camera_Texture2D, 0, 1, &Region, VideoSize.X * 4, 4, (uint8*)ColorData.GetData(), false);

    return true;
}




