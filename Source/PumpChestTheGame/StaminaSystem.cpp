// Written by Juno Suwanduan

#include "StaminaSystem.h"

StaminaSystem::StaminaSystem(int maxStamina)
    : currentStamina(maxStamina), maxStamina(maxStamina) {}

void StaminaSystem::DepleteStamina(int amount) {
    if (currentStamina >= amount) {
        currentStamina -= amount;
    }
}

void StaminaSystem::RecoverStamina(int amount) {
    currentStamina = (currentStamina + amount > maxStamina) ? maxStamina : currentStamina + amount;
}

int StaminaSystem::GetCurrentStamina() const {
    return currentStamina;
}