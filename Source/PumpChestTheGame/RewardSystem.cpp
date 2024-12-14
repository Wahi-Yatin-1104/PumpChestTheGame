// Written by Juno Suwanduan

#include "RewardSystem.h"
#include <iostream>

Reward::Reward(const std::string& name, const std::string& description, int value)
    : name(name), description(description), value(value) {}

std::string Reward::GetName() const {
    return name;
}

std::string Reward::GetDescription() const {
    return description;
}

int Reward::GetValue() const {
    return value;
}

void RewardSystem::AddReward(const Reward& reward) {
    rewards[reward.GetName()] = reward;
}

void RewardSystem::GrantReward(const std::string& rewardName) {
    auto it = rewards.find(rewardName);
    if (it != rewards.end()) {
        std::cout << "Reward Granted: " << it->second.GetName() 
                  << "\nDescription: " << it->second.GetDescription() 
                  << "\nValue: " << it->second.GetValue() << "\n\n";
    } else {
        std::cout << "Reward not found: " << rewardName << "\n";
    }
}

void RewardSystem::DisplayRewards() const {
    for (const auto& pair : rewards) {
        std::cout << "Reward: " << pair.second.GetName() 
                  << "\nDescription: " << pair.second.GetDescription() 
                  << "\nValue: " << pair.second.GetValue() << "\n\n";
    }
}