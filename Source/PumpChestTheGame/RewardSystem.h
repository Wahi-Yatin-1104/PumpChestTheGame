// Written by Juno Suwanduan

#ifndef REWARD_SYSTEM_H
#define REWARD_SYSTEM_H

#include <string>
#include <vector>
#include <unordered_map>

class Reward {
public:
    Reward(const std::string& name, const std::string& description, int value);
    std::string GetName() const;
    std::string GetDescription() const;
    int GetValue() const;

private:
    std::string name;
    std::string description;
    int value;
};

class RewardSystem {
public:
    void AddReward(const Reward& reward);
    void GrantReward(const std::string& rewardName);
    void DisplayRewards() const;

private:
    std::unordered_map<std::string, Reward> rewards;
};

#endif