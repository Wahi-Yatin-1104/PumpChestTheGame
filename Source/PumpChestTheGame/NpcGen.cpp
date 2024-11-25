#include "NpcGen.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

ANpcGen::ANpcGen()
{
    PrimaryActorTick.bCanEverTick = true;

    WalkSpeed = 300.0f;
    RotationSpeed = 90.0f;
    Health = 100.0f;
    MaxHealth = 100.0f;
    WanderRadius = 500.0f;
    WanderInterval = 5.0f;

    TextBoxWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextBoxWidget"));
    TextBoxWidget->SetupAttachment(RootComponent);
    TextBoxWidget->SetWidgetSpace(EWidgetSpace::Screen);
    TextBoxWidget->SetDrawSize(FVector2D(200, 50));
    TextBoxWidget->SetVisibility(false);

    TextMessages = { "Hello!", "Goodbye!" };
}

void ANpcGen::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(WanderTimerHandle, this, &ANpcGen::RandomMovement, WanderInterval, true);
}

void ANpcGen::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Patrol();
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
}

void ANpcGen::Patrol()
{
    if (PatrolWaypoints.Num() > 0)
    {
        static int32 CurrentWaypointIndex = 0;
        AActor* CurrentWaypoint = PatrolWaypoints[CurrentWaypointIndex];

        if (CurrentWaypoint)
        {
            FVector DirectionToWaypoint = CurrentWaypoint->GetActorLocation() - GetActorLocation();
            DirectionToWaypoint.Z = 0;
            DirectionToWaypoint.Normalize();

            AddMovementInput(DirectionToWaypoint, WalkSpeed * GetWorld()->GetDeltaSeconds());

            float DistanceToWaypoint = FVector::Dist(CurrentWaypoint->GetActorLocation(), GetActorLocation());
            if (DistanceToWaypoint < 100.0f)
            {
                CurrentWaypointIndex = (CurrentWaypointIndex + 1) % PatrolWaypoints.Num();
            }
        }
    }
}

void ANpcGen::GreetPlayer()
{
    DisplayRandomTextBox(5.0f);
}

void ANpcGen::TakeDamage(float DamageAmount)
{
    Health -= DamageAmount;
    if (Health <= 0.0f)
    {
        Die();
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("NPC Health: %f"), Health));
        }
    }
}

void ANpcGen::Die()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NPC Died"));
    }
    Destroy();
}

void ANpcGen::Jump()
{
    ACharacter::Jump();
}
/* :D
void ANpcGen::Tbag()
{
    ACharacter::Tbag();
}
*/
void ANpcGen::StandUp()
{
    ACharacter::UnCrouch();
}

void ANpcGen::Wander()
{
    FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();
    RandomDirection.Z = 0;
    AddMovementInput(RandomDirection, WalkSpeed * GetWorld()->GetDeltaSeconds());
}

void ANpcGen::Stop()
{
    GetCharacterMovement()->StopMovementImmediately();
}

void ANpcGen::RotateTowards(FVector TargetLocation)
{
    FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
    SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed));
}

void ANpcGen::LookAtPlayer(ACharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        RotateTowards(PlayerCharacter->GetActorLocation());
    }
}

void ANpcGen::RandomMovement()
{
    FVector RandomLocation = GetActorLocation() + UKismetMathLibrary::RandomUnitVector() * WanderRadius;
    FVector Direction = RandomLocation - GetActorLocation();
    Direction.Z = 0;
    Direction.Normalize();
    AddMovementInput(Direction, WalkSpeed * GetWorld()->GetDeltaSeconds());
}

void ANpcGen::IdleBehavior()
{
    // Example idle behavior: play idle animation or perform random actions
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("NPC is idling"));
    }
}

void ANpcGen::InteractWithEnvironment()
{
    // Example interaction: open a door or pick up an item
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NPC is interacting with the environment"));
    }
}

void ANpcGen::StartDialogue()
{
    // Example dialogue initiation
    DisplayRandomTextBox(5.0f);
}

void ANpcGen::RegenerateHealth()
{
    // Example health regeneration over time
    if (Health < MaxHealth)
    {
        Health += 1.0f; // Adjust the regeneration rate as needed
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("NPC Health: %f"), Health));
        }
    }
}

void ANpcGen::Alert()
{
    // Example alert behavior: change color or play alert animation
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("NPC is alert"));
    }
}

void ANpcGen::FleeFromDanger()
{
    // Example flee behavior: move away from a danger source
    FVector FleeDirection = -GetActorForwardVector();
    AddMovementInput(FleeDirection, WalkSpeed * GetWorld()->GetDeltaSeconds());
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("NPC is fleeing from danger"));
    }
}

void ANpcGen::PerformTask()
{
    // Example task performance: farming, crafting, etc.
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("NPC is performing a task"));
    }
}
