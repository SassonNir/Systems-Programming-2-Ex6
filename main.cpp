#include <algorithm>
#include <deque>

#include "League.hpp"
#include "Schedule.hpp"
using namespace basketball;

int main() {
    std::vector<Team*> teams;
    teams.push_back(new Team("Lakers", 0.9));
    teams.push_back(new Team("Celtics", 0.8));
    teams.push_back(new Team("Warriors", 0.7));
    teams.push_back(new Team("Rockets", 0.6));
    teams.push_back(new Team("Spurs", 0.5));
    teams.push_back(new Team("Clippers", 0.4));
    teams.push_back(new Team("Kings", 0.3));
    teams.push_back(new Team("Nuggets", 0.2));
    teams.push_back(new Team("Jazz", 0.1));
    teams.push_back(new Team("Hawks", 0.0));
    teams.push_back(new Team("Grizzlies", 0.46453));
    teams.push_back(new Team("Pelicans", 0.8675));
    teams.push_back(new Team("Timberwolves", 0.24234));
    teams.push_back(new Team("Mavericks", 0.54321));
    teams.push_back(new Team("Nets", 0.12345));
    teams.push_back(new Team("Suns", 0.98765));
    teams.push_back(new Team("Trail Blazers", 0.09876));
    // teams.push_back(new Team("Jazz", 0.09876)); // This team is already in the vector throws an exception
    teams.push_back(new Team("Pistons", 0.8503));
    teams.push_back(new Team("Raptors", 0.6546));
    teams.push_back(new Team("Grizzlies", 0.6546)); // This team is already in the vector throws an exception
    // teams.push_back(new Team("Hornets", 0.54321));
    // teams.push_back(new Team("Bucks", 0.12345)); // More than TEAMS_COUNT teams prints an error message

    // League League(teams);

    // std::cout << League << std::endl;

    // std::vector<Team*> teams;
    // teams.push_back(new Team("1", 0.9));
    // teams.push_back(new Team("2", 0.8));
    // teams.push_back(new Team("3", 0.7));
    // teams.push_back(new Team("4", 0.6));
    // teams.push_back(new Team("5", 0.5));
    // teams.push_back(new Team("6", 0.4));
    // teams.push_back(new Team("7", 0.3));
    // teams.push_back(new Team("8", 0.2));

    League League(teams);
    // Schedule schedule(&League);

    // std::cout << League << std::endl;
    League.end_season(3);

    // for (auto& game : League) {
    //     std::cout << game.get_away()->get_name() << std::endl;
    // }
    // std::cout << schedule << std::endl;
    // League::StatsIterator iter = League.begin();

    // std::cout << iter << std::endl;
    // while (iter != League.end()) {
    //     // Game game = *iter;
    //     // std::cout << iter << std::endl;
    //     // std::cout << iter.game_count << ": " << game.get_home()->get_name() << " vs " << game.get_away()->get_name() << std::endl;
    //     ++iter;
    // }
    // std::cout << iter << std::endl;
    return 0;
}