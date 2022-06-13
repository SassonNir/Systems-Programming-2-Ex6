#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

namespace basketball {
class Team {
   private:
    std::string name;
    double skills;

   public:
    Team(std::string name, double skills = 0.0);
    ~Team(void) {}

    std::string get_name(void) const;
    double get_skills(void) const;
    Team* set_name(std::string name);
    Team* set_skills(double skills);

    friend std::ostream& operator<<(std::ostream& os, const Team& team);
    friend std::ostream& operator<<(std::ostream& os, const Team* team);
};
}  // namespace basketball