// Written by Juno Suwanduan

#ifndef SKILL_PROGRESSION_SYSTEM_H
#define SKILL_PROGRESSION_SYSTEM_H

#include <string>
#include <unordered_map>

class Skill {
public:
    Skill(const std::string& name, int level, int experience);
    std::string GetName() const;
    int GetLevel() const;
    int GetExperience() const;
    void AddExperience(int amount);

private:
    std::string name;
    int level;
    int experience;
    void LevelUp();
};

class SkillProgressionSystem {
public:
    void AddSkill(const Skill& skill);
    void GainExperience(const std::string& skillName, int amount);
    void DisplaySkills() const;

private:
    std::unordered_map<std::string, Skill> skills;
};

#endif