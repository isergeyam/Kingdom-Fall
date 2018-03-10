//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CFIELD_HPP
#define GAME_PROJ_CFIELD_HPP


#include <vector>
#include <string>
#include "CObject.hpp"

class CField : public CObject {
private:
    std::string m_name;
public:
    static std::vector<std::string> EFields;
};


#endif //GAME_PROJ_CFIELD_HPP
