// Written by Juno Suwanduan

#ifndef WORKOUT_PLAN_SYSTEM_H
#define WORKOUT_PLAN_SYSTEM_H

#include <string>
#include <vector>

struct WorkoutPlan {
    std::string name;
    std::vector<std::string> exercises;
    int duration; // in minutes
};

class WorkoutPlanSystem {
public:
    void CreateWorkoutPlan(const std::string& name, const std::vector<std::string>& exercises, int duration);
    void DisplayWorkoutPlans() const;

private:
    std::vector<WorkoutPlan> plans;
};

#endif