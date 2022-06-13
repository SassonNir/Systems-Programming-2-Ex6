#include "Team.hpp"

namespace basketball {
Team::Team(std::string name, double skills) {
    this->set_name(name);
    this->set_skills(skills);
}

std::string Team::get_name(void) const {
    return this->name;
}

double Team::get_skills(void) const {
    return this->skills;
}

Team* Team::set_name(std::string name) {
    if (name.empty()) {
        throw std::invalid_argument("Team name cannot be empty");
    } else {
        this->name = name;
    }
    return this;
}

Team* Team::set_skills(double skills) {
    if (skills < 0.0 || skills > 1.0) {
        throw std::invalid_argument("Team skills must be between 0.0 and 1.0");
    } else {
        this->skills = skills;
    }
    return this;
}

std::ostream& operator<<(std::ostream& os, const Team& team) {
    os << team.get_name() << ": " << team.get_skills();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Team* team) {
    os << *team;
    return os;
}

}  // namespace basketball