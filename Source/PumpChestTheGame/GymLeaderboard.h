// Written by Juno Suwanduan

#ifndef GYM_LEADERBOARD_H
#define GYM_LEADERBOARD_H

#include <string>
#include <vector>
#include <map>

class GymLeaderboard {
public:
    void AddScore(const std::string& playerName, int score);
    void DisplayLeaderboard() const;
    void ResetLeaderboard();
    int GetPlayerRank(const std::string& playerName) const;
    void SaveLeaderboard(const std::string& filename) const;
    void LoadLeaderboard(const std::string& filename);

private:
    std::multimap<int, std::string, std::greater<int>> scores;
};

#endif