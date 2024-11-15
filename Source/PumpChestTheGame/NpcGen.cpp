#include "NpcGen.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h" 

ANpcGen::ANpcGen()
{
    PrimaryActorTick.bCanEverTick = true;

    WalkSpeed = 300.0f;
    RotationSpeed = 90.0f; 

    TextBoxWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextBoxWidget"));
    TextBoxWidget->SetupAttachment(RootComponent);
    TextBoxWidget->SetWidgetSpace(EWidgetSpace::Screen);
    TextBoxWidget->SetDrawSize(FVector2D(200, 50));
    TextBoxWidget->SetVisibility(false);

    TextMessages = { "Hello!", "How are you?", "Nice to meet you!", "Goodbye!" };
}

void ANpcGen::BeginPlay()
{
    Super::BeginPlay();
}

void ANpcGen::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /* use this to test but it slows performance significantly 
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        // Call the FollowAndStop function
        FollowAndStop(PlayerCharacter);
    }
    */
}

void ANpcGen::MoveInCircles(float DeltaTime)
{
    if (Controller)
    {
        AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));

        const FVector Direction = GetActorForwardVector();
        AddMovementInput(Direction, WalkSpeed * DeltaTime);
    }
}

void ANpcGen::DisplayRandomTextBox(float Duration)
{
    if (TextBoxWidget && TextMessages.Num() > 0)
    {
        int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, TextMessages.Num() - 1);
        FString RandomText = TextMessages[RandomIndex];

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Displaying Text: %s"), *RandomText));
        }

        UUserWidget* Widget = TextBoxWidget->GetUserWidgetObject();
        if (Widget)
        {
            UFunction* SetTextFunction = Widget->FindFunction(FName("SetDisplayedText"));
            if (SetTextFunction)
            {
                struct FSetTextParams
                {
                    FText Text;
                };

                FSetTextParams Params;
                Params.Text = FText::FromString(RandomText);

                Widget->ProcessEvent(SetTextFunction, &Params);
            }
        }

        TextBoxWidget->SetVisibility(true);
        GetWorld()->GetTimerManager().SetTimer(TextBoxTimerHandle, this, &ANpcGen::HideTextBox, Duration, false);
    }
}

void ANpcGen::HideTextBox()
{
    if (TextBoxWidget)
    {
        TextBoxWidget->SetVisibility(false);
    }
}

void ANpcGen::FollowAndStop(ACharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        FVector DirectionToPlayer = PlayerCharacter->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0;
        DirectionToPlayer.Normalize();

        AddMovementInput(DirectionToPlayer, WalkSpeed * GetWorld()->GetDeltaSeconds());

        FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerCharacter->GetActorLocation());
        SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed));

        float DistanceToPlayer = FVector::Dist(PlayerCharacter->GetActorLocation(), GetActorLocation());
        if (DistanceToPlayer < 200.0f) 
        {
            DisplayRandomTextBox(5.0f);
            GetWorld()->GetTimerManager().SetTimer(StopTimerHandle, this, &ANpcGen::ResumeMovement, 30.0f, false);
        }
    }
}

void ANpcGen::ResumeMovement()
{
    //yes, this is totally correct
}
