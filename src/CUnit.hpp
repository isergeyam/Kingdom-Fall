//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNIT_HPP
#define GAME_PROJ_CUNIT_HPP


#include <map>
#include <vector>
#include "CObject.hpp"
#include "CField.hpp"
typedef char Percent_t;
typedef size_t Strength_t;
class CUnit : public CObject {
public:
    struct Ability_t{
        Strength_t m_stregth;
        Percent_t m_agility;
        bool is_ranged;

    };
private:
    Health_t m_health;
    std::string m_race;
    std::string m_type;
    std::map<std::string, Percent_t> m_patency;
    std::vector<Ability_t> m_ability;
    std::map<std::string, Percent_t > m_resistance;
};


#endif //GAME_PROJ_CUNIT_HPP
