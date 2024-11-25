#include "Vehicle.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

AVehicle::AVehicle()
{
    // Def not a main priority but I hate how cars are hard to give physics.
    PrimaryActorTick.bCanEverTick = true;

    VehicleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VehicleMesh"));
    RootComponent = VehicleMesh;

    DriveSpeed = 1000.0f;
    DetectionRange = 500.0f;
}

void AVehicle::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AVehicle::PerformAction, 5.0f, true);
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Call your custom functions here
   // DriveForward();
   // CheckForObstacles();
}

void AVehicle::DriveForward()//BROKEN DO NOT UNCOMMENT, CRASHES EDITOR
{
  //  FVector Velocity = GetActorForwardVector() * DriveSpeed;
   // VehicleMesh->SetPhysicsLinearVelocity(Velocity);
}

void AVehicle::CheckForObstacles()
{
    FHitResult HitResult;
    FVector Start = GetActorLocation();
    FVector End = Start + (GetActorForwardVector() * DetectionRange);

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        if (HitResult.GetActor() != nullptr)
        {
            StopVehicle();
        }
    }
}

void AVehicle::StopVehicle()
{
    VehicleMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

void AVehicle::PerformAction()
{
   //Fix eventually
}
