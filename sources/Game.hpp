#pragma once
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

#include "Team.hpp"

#define MEAN(l, u) (u + l) / 2.0
#define STDDEV(l, u) (u - l) / 2.0

#define MIN_HOME 55.0
#define MAX_HOME 100.0
#define MIN_AWAY 50.0
#define MAX_AWAY 100.0

#define MAX_SKILL_BONUS 10.0

namespace basketball {
class Game {
   private:
    static std::random_device rd_;
    static std::mt19937 gen_;
    Team* home_;
    Team* away_;
    bool started_;
    unsigned short home_score_;  // 0 to 65535 (I could have use bit fields but it's not worth it)
    unsigned short away_score_;  // 0 to 65535 (I could have use bit fields but it's not worth it)
   public:
    Game(Team& home, Team& away) : home_(&home), away_(&away), home_score_(0), away_score_(0), started_(false) {}
    Game(Team* home, Team* away) : home_(home), away_(away), home_score_(0), away_score_(0), started_(false) {}
    ~Game(void) {}
    Team* winner(void);  // returns a pointer to the winning team, if tie choose randomly. if no winner returns nullptr (game is not over)
    void play(void);
    Team* get_home(void) const { return home_; }
    Team* get_away(void) const { return away_; }
    unsigned short get_home_score(void) const { return home_score_; }
    unsigned short get_away_score(void) const { return away_score_; }
};

}  // namespace basketball
