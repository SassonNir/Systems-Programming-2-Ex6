#include "Schedule.hpp"

namespace basketball {

Schedule& Schedule::operator++() {
    if (this->round >= this->size - 1 && !this->is_swap) {
        this->game = nullptr;
        return *this;
    }
    if (is_swap) {
        this->game = new Game(this->game->get_away(), this->game->get_home());
        is_swap = false;
        return *this;
    }

    Team *team1 = this->teams.at(this->indexes[this->index]);
    Team *team2 = this->teams.at(this->indexes[this->size - 1 - this->index]);
    if (team1 == nullptr || team2 == nullptr) {
        return ++(*this);
    }
    this->game = new Game(team1, team2);
    is_swap = true;

    ++this->index;
    if (this->index >= this->size / 2) {
        ++this->round;
        this->index = 0;
        size_t f = this->indexes.front();
        this->indexes.pop_front();
        std::rotate(this->indexes.begin(), this->indexes.end() - 1, this->indexes.end());
        this->indexes.push_front(f);
    }
    return *this;
}

// Prints Statistics of the games in the schedule
std::ostream& operator<<(std::ostream& os, const Schedule& schedule) {
    os << "Schedule:" << std::endl;

    return os;
}

}  // namespace basketball