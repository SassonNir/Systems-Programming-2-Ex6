#include "Game.hpp"
#include "League.hpp"
#include "Schedule.hpp"
#include "Team.hpp"
#include "doctest.h"

using namespace basketball;
using namespace std;

TEST_CASE("Schedule") {
    std::vector<Team*> teams;
    teams.push_back(new Team("1", 0.5));
    teams.push_back(new Team("2", 0.5));
    teams.push_back(new Team("3", 0.5));
    teams.push_back(new Team("4", 0.5));
    teams.push_back(new Team("5", 0.5));
    teams.push_back(new Team("6", 0.5));
    teams.push_back(new Team("7", 0.5));
    teams.push_back(new Team("8", 0.5));
    teams.push_back(new Team("9", 0.5));
    teams.push_back(new Team("10", 0.5));
    teams.push_back(new Team("11", 0.5));
    teams.push_back(new Team("12", 0.5));
    teams.push_back(new Team("13", 0.5));
    teams.push_back(new Team("14", 0.5));
    teams.push_back(new Team("15", 0.5));
    teams.push_back(new Team("16", 0.5));
    teams.push_back(new Team("17", 0.5));
    teams.push_back(new Team("18", 0.5));
    teams.push_back(new Team("19", 0.5));
    teams.push_back(new Team("20", 0.5));

    // League league(teams);
    Schedule schedule(teams);
    unordered_map<string, vector<string>> schedule_map;
    long game_count = 0;
    for (auto& game : schedule) {
        string away = game.get_away()->get_name();
        string home = game.get_home()->get_name();
        schedule_map[home].push_back(away);
        game_count++;
    }
    CHECK(game_count == (teams.size() * (teams.size() - 1)));
    for (auto& s : schedule_map) {
        CHECK(s.second.size() == teams.size() - 1);
        for (int i = 0; i < teams.size() - 1; i++) {
            string v = to_string(i + 1);
            if (v != s.first) {
                CHECK(find(s.second.begin(), s.second.end(), v) != s.second.end());
            }
        }
    }
}

TEST_CASE("League") {
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
    teams.push_back(new Team("Pistons", 0.8503));
    teams.push_back(new Team("Raptors", 0.6546));
    
    teams.push_back(new Team("Grizzlies", 0.6546)); // This team is already in the vector throws an exception
    // teams.push_back(new Team("Bucks", 0.12345)); // More than TEAMS_COUNT teams prints an error message
    // teams.push_back(new Team("Jazz", 0.09876)); // This team is already in the vector throws an exception

    CHECK_THROWS(new League(teams));
    teams.pop_back();
    teams.push_back(new Team("Hornets", 0.54321));
    CHECK_NOTHROW(new League(teams));
    teams.pop_back();
    teams.pop_back();
    CHECK_NOTHROW(new League(teams));
    League league(teams);
    CHECK(league.get_teams().size() == TEAMS_COUNT);
    unordered_map<string, vector<string>> schedule_map;
    long game_count = 0;
    for (auto& game : league) {
        string away = game.get_away()->get_name();
        string home = game.get_home()->get_name();
        schedule_map[home].push_back(away);
        game_count++;
    }
    CHECK(game_count == (TEAMS_COUNT * (TEAMS_COUNT - 1)));
    for (auto& s : schedule_map) {
        CHECK(s.second.size() == TEAMS_COUNT - 1);
        for (auto& v : league.get_teams()) {
            if (v->get_name() != s.first) {
                CHECK(find(s.second.begin(), s.second.end(), v->get_name()) != s.second.end());
            }
        }
    }
}
