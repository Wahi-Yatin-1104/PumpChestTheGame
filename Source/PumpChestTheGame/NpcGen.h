#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NpcGen.generated.h"

UCLASS()
class LOCALTESTING_API ANpcGen : public ACharacter
{   //ALTER THIS to the name of the game, LOCALTESTING is my local run
    GENERATED_BODY()

public:
    ANpcGen();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    //NPC run in circles, Use for testing
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveInCircles(float DeltaTime);

    // Function to display a random text box above the NPC's head
    UFUNCTION(BlueprintCallable, Category = "UI")
    void DisplayRandomTextBox(float Duration);

    // follows player ideally
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void FollowAndStop(ACharacter* PlayerCharacter);

    // default for move
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ResumeMovement();

    //I hate that this isnt working
    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideTextBox();

private:
    // speed of the NPC
    UPROPERTY(EditAnywhere, Category = "Movement")
    float WalkSpeed;

    // rotates the npc towards a direction
    UPROPERTY(EditAnywhere, Category = "Movement")
    float RotationSpeed;

    //display text box
    UPROPERTY(VisibleAnywhere, Category = "UI")
    class UWidgetComponent* TextBoxWidget;

    // Timers/texts, in development
    FTimerHandle TextBoxTimerHandle;
    FTimerHandle StopTimerHandle;
    UPROPERTY(EditAnywhere, Category = "Text")
    TArray<FString> TextMessages;
};
