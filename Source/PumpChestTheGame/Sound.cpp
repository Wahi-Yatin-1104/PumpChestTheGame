#include "Sound.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
ASound::ASound()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create audio components
    BackgroundMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundMusicComponent"));
    BackgroundMusicComponent->SetupAttachment(RootComponent);

    SoundEffectComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEffectComponent"));
    SoundEffectComponent->SetupAttachment(RootComponent);

    VoiceoverComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VoiceoverComponent"));
    VoiceoverComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASound::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASound::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to play background music
void ASound::PlayBackgroundMusic(USoundBase* Music)
{
    if (Music)
    {
        BackgroundMusicComponent->SetSound(Music);
        BackgroundMusicComponent->Play();
    }
}

// Function to play a sound effect
void ASound::PlaySoundEffect(USoundBase* SoundEffect)
{
    if (SoundEffect)
    {
        SoundEffectComponent->SetSound(SoundEffect);
        SoundEffectComponent->Play();
    }
}

// Function to play a voiceover
void ASound::PlayVoiceover(USoundBase* Voiceover)
{
    if (Voiceover)
    {
        VoiceoverComponent->SetSound(Voiceover);
        VoiceoverComponent->Play();
    }
}
