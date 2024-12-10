#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NpcGen.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API ANpcGen : public ACharacter
{
    GENERATED_BODY()

public:
    ANpcGen();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveInCircles(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void DisplayRandomTextBox(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void FollowAndStop(ACharacter* PlayerCharacter);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ResumeMovement();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideTextBox();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Patrol();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void GreetPlayer();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TakeDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Die();

    void Jump() override;

    //void Tbag(); maybe . . 

    void StandUp();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Wander();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Stop();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void RotateTowards(FVector TargetLocation);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void LookAtPlayer(ACharacter* PlayerCharacter);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void RandomMovement();

    UFUNCTION(BlueprintCallable, Category = "Behavior")
    void IdleBehavior();

    UFUNCTION(BlueprintCallable, Category = "Environment")
    void InteractWithEnvironment();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void StartDialogue();

    UFUNCTION(BlueprintCallable, Category = "Health")
    void RegenerateHealth();

    UFUNCTION(BlueprintCallable, Category = "Alert")
    void Alert();

    UFUNCTION(BlueprintCallable, Category = "Flee")
    void FleeFromDanger();

    UFUNCTION(BlueprintCallable, Category = "Tasks")
    void PerformTask();

private:
    UPROPERTY(EditAnywhere, Category = "Movement")
    float WalkSpeed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float RotationSpeed;

    UPROPERTY(VisibleAnywhere, Category = "UI")
    class UWidgetComponent* TextBoxWidget;

    FTimerHandle TextBoxTimerHandle;
    FTimerHandle StopTimerHandle;
    UPROPERTY(EditAnywhere, Category = "Text")
    TArray<FString> TextMessages;

    UPROPERTY(EditAnywhere, Category = "Movement")
    TArray<AActor*> PatrolWaypoints;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float Health;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float MaxHealth;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float WanderRadius;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float WanderInterval;

    FTimerHandle WanderTimerHandle;
};
