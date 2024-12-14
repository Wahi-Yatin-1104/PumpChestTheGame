// Written by Juno Suwanduan

#ifndef STAMINA_SYSTEM_H
#define STAMINA_SYSTEM_H

class StaminaSystem {
public:
    StaminaSystem(int maxStamina);
    void DepleteStamina(int amount);
    void RecoverStamina(int amount);
    int GetCurrentStamina() const;

private:
    int currentStamina;
    int maxStamina;
};

#endif