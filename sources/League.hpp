#pragma once
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <tuple>
#include <map>
#include <set>
#include <vector>

#include "Game.hpp"
#include "Schedule.hpp"
#include "Team.hpp"
#include "tableprinter.hpp"

#define TEAMS_COUNT 20
// #define TEAMS_COUNT 8
#define MIN_RAND_NAME_LENGTH 5   // minimum length of a random name
#define MAX_RAND_NAME_LENGTH 10  // maximum length of a random name

namespace basketball {
class League {
    friend class StatsIterator;

   private:
    std::map<std::string, Team*> teams;
    // std::unordered_map<std::string, Team*> teams;
    static std::random_device rd_;
    static std::mt19937 gen_;

   protected:
    struct Statistics {
       public:
        Team* team;
        long home_plays;
        long away_plays;
        long home_wins;
        long away_wins;
        long total_score;
        long total_opponent_score;
        long total_games() const {
            return home_plays + away_plays;
        }
        long total_wins() const {
            return home_wins + away_wins;
        }
        long total_losses() const {
            return total_games() - total_wins();
        }
        double home_win_percentage() const {
            if (total_games() == 0) {
                return 0.0;
            }
            return (double)home_wins / (double)home_plays;
        }
        double away_win_percentage() const {
            if (away_plays == 0) {
                return 0.0;
            }
            return (double)away_wins / (double)away_plays;
        }
        double total_win_percentage() const {
            if (total_losses() == 0) {
                return 0.0;
            }
            return (double)total_wins() / (double)total_games();
        }
        double total_loss_percentage() const {
            if (total_losses() == 0) {
                return 0.0;
            }
            return (double)total_losses() / (double)total_games();
        }
        double win_loss_ratio() const {
            if (total_losses() == 0) {
                return 0.0;
            }
            return (double)total_wins() / (double)total_losses();
        }
        long total_score_difference() const {
            return total_score - total_opponent_score;
        }
    };

    struct StatisticsComparator {
        bool operator()(const Statistics& lhs, const Statistics& rhs) const {
            if (lhs.win_loss_ratio() != rhs.win_loss_ratio()) {
                return lhs.win_loss_ratio() > rhs.win_loss_ratio();
            }
            return lhs.total_score_difference() > rhs.total_score_difference();
        }
    };

   public:
    League(std::vector<Team*> teams = {});
    ~League(void);

    std::vector<Team*> get_teams(void) const {
        std::vector<Team*> teams;
        for (auto& team : this->teams) {
            teams.push_back(team.second);
        }
        return teams;
    }

    class StatsIterator : public Schedule {
        friend class League;

       public:
        size_t game_count;
        std::map<Team*, Statistics*> team_stats;
        StatsIterator() : Schedule(), game_count(0) {}
        StatsIterator(std::vector<Team*> teams) : Schedule(teams), game_count(0) {
            for (auto& team : this->teams) {
                this->team_stats[team] = new Statistics{team, 0, 0, 0, 0};
            }
        }
        ~StatsIterator(void) {}

        Team* get_home(void) const {
            return this->game->get_home();
        }
        Team* get_away(void) const {
            return this->game->get_away();
        }

        std::set<Statistics, League::StatisticsComparator> get_stats(void) const {
            std::set<Statistics, League::StatisticsComparator> stats;
            // stats.insert(this->team_stats.at(this->get_home()));
            for (const auto& team_stat : this->team_stats) {
                stats.insert(*team_stat.second);
                // stats.insert(const_cast<Statistics*>(team_stat.second));
            }
            return stats;
        }

        StatsIterator& operator++() {
            Schedule::operator++();
            if (this->game != nullptr) {
                this->game->play();
                this->team_stats[this->get_home()]->home_plays++;
                this->team_stats[this->get_away()]->away_plays++;
                Team* winner = this->game->winner();
                if (winner == nullptr) {
                    throw std::invalid_argument("Error in a game between " + this->get_home()->get_name() + " and " + this->get_away()->get_name());
                }
                if (winner == this->get_home()) {
                    this->team_stats[this->get_home()]->home_wins++;
                } else {
                    this->team_stats[this->get_away()]->away_wins++;
                }
                this->team_stats[this->get_home()]->total_score += this->game->get_home_score();
                this->team_stats[this->get_away()]->total_score += this->game->get_away_score();
                this->team_stats[this->get_home()]->total_opponent_score += this->game->get_away_score();
                this->team_stats[this->get_away()]->total_opponent_score += this->game->get_home_score();
                this->game_count++;
            }

            return *this;
        }


        static tableprinter::printer get_print(std::ostream& os) {
            // using namespace tableprinter;
            tableprinter::printer p{
                {
                    {tableprinter::name{"Team"}, tableprinter::width{20}, tableprinter::left{}},
                    {tableprinter::name{"Win Loss Ratio"}, tableprinter::width{20}, tableprinter::fixed{}, tableprinter::precision{4}, tableprinter::left{}},
                    {tableprinter::name{"Score Difference"}, tableprinter::width{20}, tableprinter::left{}},
                    /* {tableprinter::name{"Total Games"}, tableprinter::width{15}, tableprinter::left{}}, */
                    {tableprinter::name{"Total Wins"}, tableprinter::width{15}, tableprinter::left{}},
                    {tableprinter::name{"Total Losses"}, tableprinter::width{15}, tableprinter::left{}},
                    {tableprinter::name{"Home Win %"}, tableprinter::width{16}, tableprinter::fixed{}, tableprinter::precision{4}, tableprinter::left{}},
                    {tableprinter::name{"Away Win %"}, tableprinter::width{16}, tableprinter::fixed{}, tableprinter::precision{4}, tableprinter::left{}},
                    {tableprinter::name{"Total Win %"}, tableprinter::width{17}, tableprinter::fixed{}, tableprinter::precision{4}, tableprinter::left{}},
                    {tableprinter::name{"Total Loss %"}, tableprinter::width{17}, tableprinter::fixed{}, tableprinter::precision{4}, tableprinter::left{}},
                },
                {os}};
            p.sanity_check();
            return p;
        }

        friend std::ostream& operator<<(std::ostream& os, const StatsIterator& it) {
            // using namespace tableprinter;
            tableprinter::printer p = StatsIterator::get_print(os);
            p.print_headers();
            for (const auto& stat : it.get_stats()) {
                p.print(stat.team->get_name(), stat.win_loss_ratio(), stat.total_score_difference(), /* stat.total_games(), */ stat.total_wins(), stat.total_losses(), stat.home_win_percentage(), stat.away_win_percentage(), stat.total_win_percentage(), stat.total_loss_percentage());
            }
            return os;
        }
        friend std::ostream& operator<<(std::ostream& os, const StatsIterator* it) {
            return os << *it;
        }

    };

    StatsIterator begin() const {
        std::vector<Team*> teams;
        for (auto& team : this->teams) {
            teams.push_back(team.second);
        }
        return StatsIterator(teams);
    }

    StatsIterator end() const {
        return StatsIterator();
    }

    Game* game(Team* home, Team* away);

    friend std::ostream& operator<<(std::ostream& os, const League& League) {
        StatsIterator stat_iter = League.begin();
        while (stat_iter != League.end()) {
            ++stat_iter;
        }
        os << stat_iter;
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const League* League) {
        return os << *League;
    }

    void end_season(int top_n = TEAMS_COUNT) {
        std::cout << "End of season" << std::endl
                  << "Season stats:" << std::endl;
        StatsIterator stat_iter = this->begin();
        std::unordered_map <Team*, std::tuple<int, int, int, int>> stats_track; // <longest win streak, longest loss streak, total score, total opponents score>
        for (auto team : this->teams) {
            stats_track[team.second] = std::make_tuple(0, 0, 0, 0);
        }
        while (stat_iter != this->end()) {
            Game game = *stat_iter;
            Team* home = game.get_home();
            Team* away = game.get_away();
            Statistics* home_stat = stat_iter.team_stats[home];
            Statistics* away_stat = stat_iter.team_stats[away];
            if (game.winner() == home) {
                std::get<0>(stats_track[home]) += 1;
                std::get<0>(stats_track[away]) = 0;
                std::get<1>(stats_track[home]) = 0;
                std::get<1>(stats_track[away]) += 1;
            } else {
                std::get<0>(stats_track[home]) = 0;
                std::get<0>(stats_track[away]) += 1;
                std::get<1>(stats_track[home]) += 1;
                std::get<1>(stats_track[away]) = 0;
            }
            
            std::get<2>(stats_track[home]) += game.get_home_score();
            std::get<2>(stats_track[away]) += game.get_away_score();
            std::get<3>(stats_track[home]) += game.get_away_score();
            std::get<3>(stats_track[home]) += game.get_home_score();

            ++stat_iter;
        }
        std::cout << stat_iter << std::endl;
        std::cout << "Top " << top_n << " teams:" << std::endl;

        using namespace tableprinter;
        std::set<Statistics, League::StatisticsComparator> stats = stat_iter.get_stats();
        printer p = StatsIterator::get_print(std::cout);
        p.print_headers();
        int i = 0;
        for (auto& stat : stats) {
            if (i >= top_n) {
                break;
            }
            p.print(stat.team->get_name(), stat.win_loss_ratio(), stat.total_score_difference(), /* stat.total_games(), */ stat.total_wins(), stat.total_losses(), stat.home_win_percentage(), stat.away_win_percentage(), stat.total_win_percentage(), stat.total_loss_percentage());
            i++;
        }

        std::cout << std::endl;

        std::cout << "Longest winning streak:" << std::endl;
        std::cout << "Team\t\tStreak" << std::endl;
        Team* longest_win_streak = nullptr;
        Team* longest_loss_streak = nullptr;
        int count_more_own_then_opponent = 0;
        for (auto& stat : stats) {
            if (std::get<0>(stats_track[stat.team]) > std::get<0>(stats_track[longest_win_streak])) {
                longest_win_streak = stat.team;
            }
            if (std::get<1>(stats_track[stat.team]) > std::get<1>(stats_track[longest_loss_streak])) {
                longest_loss_streak = stat.team;
            }
            if (std::get<2>(stats_track[stat.team]) > std::get<3>(stats_track[stat.team])) {
                count_more_own_then_opponent++;
            }
        }
        std::cout << longest_win_streak->get_name() << "\t\t" << std::get<0>(stats_track[longest_win_streak]) << std::endl;

        std::cout << std::endl;

        std::cout << "Longest losing streak:" << std::endl;
        std::cout << "Team\t\tStreak" << std::endl;
        std::cout << longest_loss_streak->get_name() << "\t\t" << std::get<1>(stats_track[longest_loss_streak]) << std::endl;

        std::cout << std::endl;

        std::cout << count_more_own_then_opponent << " teams have more own score than opponent score" << std::endl;


    }
};

// std::random_device League::rd_;
// std::mt19937 League::gen_ = std::mt19937(League::rd_());

}  // namespace basketball