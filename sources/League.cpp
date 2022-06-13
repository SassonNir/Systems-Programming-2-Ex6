#include "League.hpp"

namespace basketball {
std::random_device League::rd_;
std::mt19937 League::gen_ = std::mt19937(League::rd_());
League::League(std::vector<Team*> teams) {
    if (teams.size() > TEAMS_COUNT) {
        std::cerr << "Too many teams in the League, taking only the first " << TEAMS_COUNT << " teams." << " Got " << teams.size() << " teams." << std::endl;
    }
    // this->teams.reserve(TEAMS_COUNT); // Uncomment this if teams is unordered_map
    std::uniform_int_distribution<> length(MIN_RAND_NAME_LENGTH, MAX_RAND_NAME_LENGTH);
    std::uniform_int_distribution<> name(0, 'Z' - 'A');
    std::uniform_int_distribution<> lower(0, 1);
    std::uniform_real_distribution<> skills(0.0, 1.0);
    int change_case = 'a' - 'A';
    for (size_t i = 0; i < TEAMS_COUNT; i++) {
        if (i < teams.size()) {
            if (this->teams.find(teams[i]->get_name()) != this->teams.end()) {
                throw std::invalid_argument("Team name " + teams[i]->get_name() + " is already taken");
            }
            this->teams[teams[i]->get_name()] = teams[i];
        } else {
            std::string team_name;
            do {
                team_name = "";
                for (size_t j = 0; j < length(League::gen_); j++) {
                    team_name += lower(League::gen_) * change_case + ('A' + name(League::gen_));
                }
            } while (this->teams.find(team_name) != this->teams.end());
            this->teams[team_name] = new Team(team_name, skills(League::gen_));
        }
    }
}

League::~League(void) {
    for (auto& team : this->teams) {
        delete team.second;
    }
}

Game* League::game(Team* home, Team* away) {
    if (this->teams.find(home->get_name()) == this->teams.end() || this->teams.find(away->get_name()) == this->teams.end()) {
        throw std::invalid_argument("Team name " + home->get_name() + " or " + away->get_name() + " is not in the League");
    }
    if (home == away) {
        throw std::invalid_argument("Team " + home->get_name() + " cannot play against itself");
    }
    Game* game = new Game(home, away);
    return game;
}

}  // namespace basketball