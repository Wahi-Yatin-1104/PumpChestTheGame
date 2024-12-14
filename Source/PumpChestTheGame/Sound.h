#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API ASound : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASound();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to play background music
    UFUNCTION(BlueprintCallable, Category = "Sound")
    void PlayBackgroundMusic(USoundBase* Music);

    // Function to play a sound effect
    UFUNCTION(BlueprintCallable, Category = "Sound")
    void PlaySoundEffect(USoundBase* SoundEffect);

    // Function to play a voiceover
    UFUNCTION(BlueprintCallable, Category = "Sound")
    void PlayVoiceover(USoundBase* Voiceover);

private:
    // Audio component for background music
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UAudioComponent* BackgroundMusicComponent;

    // Audio component for sound effects
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UAudioComponent* SoundEffectComponent;

    // Audio component for voiceovers
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UAudioComponent* VoiceoverComponent;
};
