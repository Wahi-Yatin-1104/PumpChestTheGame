// Written by Juno Suwanduan

#include "WorkoutPlanSystem.h"
#include <iostream>

void WorkoutPlanSystem::CreateWorkoutPlan(const std::string& name, const std::vector<std::string>& exercises, int duration) {
    plans.push_back({name, exercises, duration});
}

void WorkoutPlanSystem::DisplayWorkoutPlans() const {
    for (const auto& plan : plans) {
        std::cout << "Workout Plan: " << plan.name << "\nDuration: " << plan.duration << " minutes\nExercises:\n";
        for (const auto& exercise : plan.exercises) {
            std::cout << "- " << exercise << "\n";
        }
    }
}