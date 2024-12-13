// Written by Juno Suwanduan

#include "GymLeaderboard.h"
#include <iostream>
#include <fstream>

void GymLeaderboard::AddScore(const std::string& playerName, int score) {
    scores.emplace(score, playerName);
}

void GymLeaderboard::DisplayLeaderboard() const {
    int rank = 1;
    for (const auto& pair : scores) {
        std::cout << "Rank " << rank++ << ": " << pair.second << " - " << pair.first << " points\n";
    }
}

void GymLeaderboard::ResetLeaderboard() {
    scores.clear();
}

int GymLeaderboard::GetPlayerRank(const std::string& playerName) const {
    int rank = 1;
    for (const auto& pair : scores) {
        if (pair.second == playerName) {
            return rank;
        }
        rank++;
    }
    return -1; // Player not found
}

void GymLeaderboard::SaveLeaderboard(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& pair : scores) {
        file << pair.second << "," << pair.first << "\n";
    }
    file.close();
}

void GymLeaderboard::LoadLeaderboard(const std::string& filename) {
    std::ifstream file(filename);
    std::string playerName;
    int score;
    while (file >> playerName >> score) {
        scores.emplace(score, playerName);
    }
    file.close();
}