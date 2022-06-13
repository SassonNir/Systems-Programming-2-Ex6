#pragma once
#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Game.hpp"
#include "Team.hpp"

namespace basketball {
class Schedule {
   protected:
    bool is_swap;
    std::vector<Team*> teams;
    std::deque<size_t> indexes;
    Game* game;
    size_t round;
    size_t index;
    size_t size;

   public:
    Schedule() : game(nullptr), round(0), index(0), size(0), teams({}), indexes({}), is_swap(false) {}
    Schedule(std::vector<Team*> teams) : game(nullptr), round(0), index(0), size(0), teams(teams), indexes({}), is_swap(false) {
        if (this->teams.size() < 2) {
            throw std::invalid_argument("Schedule::Schedule(): teams.size() < 2");
        } else if (this->teams.size() % 2 != 0) {
            this->teams.push_back(nullptr);
        }
        this->size = this->teams.size();

        this->indexes.resize(this->size);
        for (size_t i = 0; i < this->size; ++i) {
            // this->
            this->indexes[i] = i;
        }

        ++(*this);
    }
    ~Schedule(void) {}

    Game& operator*() const { return *game; }
    Game* operator->() { return game; }

    // Prefix increment
    virtual Schedule& operator++();

    // Postfix increment
    Schedule operator++(int) {
        Schedule tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator!=(const Schedule& other) const { return game != other.game; }
    bool operator==(const Schedule& other) const { return !(*this != other); }

    Schedule begin() { return *this; }
    Schedule end() { return Schedule(); }

    // class RoundRobin {
    //    protected:
    //     bool is_swap;
    //     League* League;
    //     std::vector<Team*> teams;
    //     std::deque<size_t> indexes;
    //     Game* game;
    //     size_t round;
    //     size_t index;
    //     size_t size;
    //    public:
    //     RoundRobin() : League(nullptr), game(nullptr), round(0), index(0), size(0), teams({}), indexes({}), is_swap(false) {}
    //     RoundRobin(League* League) : League(League), game(nullptr), round(0), index(0), is_swap(false) {
    //         if (League->teams.size() % 2 == 1) {
    //             League->teams["\0"] = nullptr;  // add a dummy team to make the number of teams even
    //         }
    //         this->size = League->teams.size();
    //         this->teams.reserve(this->size);
    //         for (auto& team : League->teams) {
    //             this->teams.push_back(team.second);
    //         }
    //         this->indexes.resize(this->size);
    //         for (size_t i = 0; i < this->size; ++i) {
    //             this->indexes[i] = i;
    //         }
    //         ++(*this);
    //     }
    //     ~RoundRobin(void) {}
    //     Game& operator*() const { return *game; }
    //     Game* operator->() { return game; }
    //     // Prefix increment
    //     virtual RoundRobin& operator++();
    //     // Postfix increment
    //     RoundRobin operator++(int) {
    //         RoundRobin tmp = *this;
    //         ++(*this);
    //         return tmp;
    //     }
    //     bool operator!=(const RoundRobin& other) const { return game != other.game; }
    //     bool operator==(const RoundRobin& other) const { return !(*this != other); }
    // };
};
}  // namespace basketball