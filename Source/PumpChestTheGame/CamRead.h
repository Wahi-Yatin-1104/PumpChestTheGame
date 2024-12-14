// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "Engine/Texture2D.h"
#include "Rendering/Texture2DResource.h"

#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MediaTexture.h"


#include "CamRead.generated.h"



UCLASS()
class PUMPCHESTTHEGAME_API ACamRead : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamRead(const  FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	USceneComponent* rootComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UStaticMeshComponent* Screen_Raw;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UStaticMeshComponent* Screen_Post;


	// The device ID opened by the Video Stream
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
	int32 CameraID;
	// The device ID opened by the Video Stream
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
	int32 VideoTrackID;
	// The rate at which the color data array and video texture is updated (in frames per second)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV, meta = (ClampMin = 0, UIMin = 0))
	float RefreshRate;
	// The refresh timer
	UPROPERTY(BlueprintReadWrite, Category = Camera)
	float RefreshTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	float Brightness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	float Multiply;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UMediaPlayer* Camera_MediaPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UMediaTexture* Camera_MediaTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UTextureRenderTarget2D* Camera_RenderTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UMaterialInstanceDynamic* Camera_MatRaw;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UMaterialInstanceDynamic* Camera_MatPost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera)
	UTexture2D* Camera_Texture2D;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Data)
	TArray<FColor> ColorData;

	// Blueprint Event called every time the video frame is updated
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
	void OnNextVideoFrame();
	// reads the current video frame
	UFUNCTION(BlueprintCallable, Category = Data)
	bool ReadFrame();

	//OpenCV
	cv::Size cvSize;
	cv::Mat cvMat;

	bool isStreamOpen;
	FVector2D VideoSize;

	void UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData);

};
