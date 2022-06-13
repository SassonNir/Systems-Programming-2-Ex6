#include "Game.hpp"

namespace basketball {

std::random_device Game::rd_;
std::mt19937 Game::gen_ = std::mt19937(Game::rd_());

Team* Game::winner(void) {
    if (!this->started_) return nullptr;
    if (this->home_score_ > this->away_score_) {
        return this->home_;
    } else if (this->home_score_ < this->away_score_) {
        return this->away_;
    }

    std::uniform_int_distribution<> dis(0, 1);
    return dis(Game::gen_) ? this->home_ : this->away_;
}

void Game::play(void) {
    if (this->started_) return;
    this->started_ = true;

    std::normal_distribution<> dis(MEAN(MIN_HOME, MAX_HOME), STDDEV(MIN_HOME, MAX_HOME));

    double home_score = dis(Game::gen_);
    std::normal_distribution<> dis2(MEAN(MIN_AWAY, MAX_AWAY), STDDEV(MIN_AWAY, MAX_AWAY));
    double away_score = dis2(Game::gen_);

    home_score += this->home_->get_skills() * MAX_SKILL_BONUS;
    away_score += this->away_->get_skills() * MAX_SKILL_BONUS;

    if (home_score < MIN_HOME) home_score = MIN_HOME;
    if (home_score > MAX_HOME) home_score = MAX_HOME;
    if (away_score < MIN_AWAY) away_score = MIN_AWAY;
    if (away_score > MAX_AWAY) away_score = MAX_AWAY;
    
    this->home_score_ = static_cast<unsigned short>(home_score);
    this->away_score_ = static_cast<unsigned short>(away_score);
}

}