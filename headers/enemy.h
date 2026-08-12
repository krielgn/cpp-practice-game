#pragma once

#include <string>
#include <vector>

#include "actor.h"

class Player;

class Enemy : public Actor {

    public:
        Enemy(int hp, int mp, int def, std::string name);
        
        std::string get_iden_str() const override { return get_name() + " is"; }

        void choose_perform_action();
        std::vector<int> get_valid_moves();
};