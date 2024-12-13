// Written by Juno Suwanduan

#include "SkillProgressionSystem.h"
#include <iostream>

Skill::Skill(const std::string& name, int level, int experience)
    : name(name), level(level), experience(experience) {}

std::string Skill::GetName() const {
    return name;
}

int Skill::GetLevel() const {
    return level;
}

int Skill::GetExperience() const {
    return experience;
}

void Skill::AddExperience(int amount) {
    experience += amount;
    if (experience >= level * 100) {
        LevelUp();
    }
}

void Skill::LevelUp() {
    level++;
    experience = 0;
    std::cout << "Skill " << name << " leveled up to " << level << "!\n";
}

void SkillProgressionSystem::AddSkill(const Skill& skill) {
    skills[skill.GetName()] = skill;
}

void SkillProgressionSystem::GainExperience(const std::string& skillName, int amount) {
    auto it = skills.find(skillName);
    if (it != skills.end()) {
        it->second.AddExperience(amount);
    } else {
        std::cout << "Skill not found: " << skillName << "\n";
    }
}

void SkillProgressionSystem::DisplaySkills() const {
    for (const auto& pair : skills) {
        std::cout << "Skill: " << pair.second.GetName() 
                  << "\nLevel: " << pair.second.GetLevel() 
                  << "\nExperience: " << pair.second.GetExperience() 
                  << "\n\n";
    }
}