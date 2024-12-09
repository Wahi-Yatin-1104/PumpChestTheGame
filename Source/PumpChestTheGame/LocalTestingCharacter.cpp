#include "LocalTestingCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "MyHUD.h"

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ALocalTestingCharacter

ALocalTestingCharacter::ALocalTestingCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...    
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character    
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    // Initialize stats
    Health = 100.0f;
    MaxHealth = 100.0f;
    Stamina = 100.0f;
    MaxStamina = 100.0f;
    Strength = 50.0f;
    Agility = 50.0f;
    Speed = 600.0f;
    MeleeDamage = 20.0f;
    RangedDamage = 15.0f;
    MeleeRange = 200.0f;
    RangedRange = 1000.0f;

    // Create mesh components
    UpperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBodyMesh"));
    UpperBodyMesh->SetupAttachment(RootComponent);

    ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
    ArmsMesh->SetupAttachment(UpperBodyMesh);

    LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegsMesh"));
    LegsMesh->SetupAttachment(RootComponent);
}

void ALocalTestingCharacter::BeginPlay()
{
    // Call the base class  
    Super::BeginPlay();

    // Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
        MyHUD = Cast<AMyHUD>(PlayerController->GetHUD());

    }
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALocalTestingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Bind actions
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALocalTestingCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALocalTestingCharacter::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALocalTestingCharacter::StartJump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ALocalTestingCharacter::StopJump);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ALocalTestingCharacter::Interact);
    }
    else
    {
        //UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }
}

// Called for movement input
void ALocalTestingCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        // Get right vector
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Add movement in that direction
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

// Called for looking input
void ALocalTestingCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // Add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ALocalTestingCharacter::Interact()
{
    //UE_LOG(LogTemplateCharacter, Log, TEXT("Interact key pressed"));
}

void ALocalTestingCharacter::StartJump()
{
    bPressedJump = true;
}

void ALocalTestingCharacter::StopJump()
{
    bPressedJump = false;
}

void ALocalTestingCharacter::StartCrouch()
{
    Crouch();
}

void ALocalTestingCharacter::StopCrouch()
{
    UnCrouch();
}

void ALocalTestingCharacter::UpdateStats()
{
    // Update character stats logic
}

void ALocalTestingCharacter::ApplyDamage(float DamageAmount)
{
    Health -= DamageAmount;
    if (Health <= 0.0f)
    {
        // Handle character death
    }
}

void ALocalTestingCharacter::RegenerateHealth(float DeltaTime)
{
    if (Health < MaxHealth)
    {
        Health += 5.0f * DeltaTime;
        if (Health > MaxHealth)
        {
            Health = MaxHealth;
        }
    }
}

void ALocalTestingCharacter::PerformMeleeAttack()
{

}

void ALocalTestingCharacter::PerformRangedAttack()
{

}

bool ALocalTestingCharacter::IsInMeleeRange(AActor* Target)
{
    if (Target)
    {
        float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
        return Distance <= MeleeRange;
    }
    return false;
}

bool ALocalTestingCharacter::IsInRangedRange(AActor* Target)
{
    if (Target)
    {
        float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());
        return Distance <= RangedRange;
    }
    return false;
}

void ALocalTestingCharacter::GainExperience(int32 Points)
{
    ExperiencePoints += Points;
    if (ExperiencePoints >= Level * 100)
    {
        Level++;
        ExperiencePoints = 0;

        //UE_LOG(LogTemplateCharacter, Log, TEXT("Leveled up to Level %d"), Level);
    }
}

void ALocalTestingCharacter::UseItem(FString ItemName)
{
    if (Inventory.Contains(ItemName))
    {
        Inventory.Remove(ItemName);
        //UE_LOG(LogTemplateCharacter, Log, TEXT("Used item: %s"), *ItemName);
    }
}

void ALocalTestingCharacter::EquipArmor(float ArmorValue)
{
    Armor = ArmorValue;
    //UE_LOG(LogTemplateCharacter, Log, TEXT("Equipped armor with value: %f"), Armor);
}

bool ALocalTestingCharacter::CheckCriticalHit()
{
    float RandomValue = FMath::FRandRange(0.0f, 1.0f);
    return RandomValue <= CriticalHitChance;
}

float ALocalTestingCharacter::ApplyCriticalHitDamage(float BaseDamage)
{
    if (CheckCriticalHit())
    {
        //UE_LOG(LogTemplateCharacter, Log, TEXT("Critical hit!"));
        return BaseDamage * CriticalHitDamage;
    }
    return BaseDamage;
}

void ALocalTestingCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Example: Update health and stamina
     UpdateHealth(Health, MaxHealth);
     UpdateStamina(Stamina, MaxStamina);
}



void ALocalTestingCharacter::UpdateHealth(float HealthValue, float MaxHealthValue)
{
    Health = HealthValue;
    MaxHealth = MaxHealthValue;
    
    if (MyHUD)
    {
        MyHUD->UpdateHealthBar(Health, MaxHealth);
    }
    
}

void ALocalTestingCharacter::UpdateStamina(float StaminaValue, float MaxStaminaValue)
{
    Stamina = StaminaValue;
    MaxStamina = MaxStaminaValue;
    
    if (MyHUD)
    {
        MyHUD->UpdateStaminaBar(Stamina, MaxStamina);
    }
    
}
