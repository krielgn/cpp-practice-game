#pragma once

#include <string>

#include "actor.h"
//#include "item.h"


class Player : public Actor {
    
    //std::vector<Item> _inventory = {};
    int _money;
    

    public:
        Player(int hp, int mp, int def);

        std::string get_iden_str() const override { return "You are"; }

        //void add_inv(Item item);    
        //void print_inv() const;
        void print_start_turn() const;

        int get_money() const { return _money; }
 
};