#pragma once

#include <vector>
#include <memory>
#include <string>

#include "action.h"

class Actor {
    protected:
        std::string _name;
        std::vector<std::unique_ptr<Action>> _moves;
        std::vector<Status> _status;
        Actor* _opponent;

        int _HP;
        int _maxHP;

        int _MP;
        int _maxMP;

        int _defense;

    public:
        Actor(int hp, int mp, int def);
        void set_opponent(Actor& a) { _opponent = &a; }
        auto get_opponent() const { return _opponent; }
        
        std::string get_name() const { return _name; }
        int get_HP() const { return _HP; }
        int get_MP() const { return _MP; }
        int get_defense() const { return _defense; }
        bool is_dead() const { return _HP <= 0; }

        void add_move(std::unique_ptr<Action> act);
        auto get_move(int in) const { return _moves[in].get(); }
        std::vector<Action*> get_moves() const;

        void apply_status(Status mod);
        void extend_status(int index, int dur);
        int has_status(std::string name) const;
        auto get_status(int in) const { return _status[in]; }

        int get_mod_num_total(ModVar var) const;

        void apply_damage(int damage);
        void apply_heal(Heal& h);
        void spend_cost(int cost) { _MP -= cost; }

        void perform(int index);
        void turn_done();

        virtual std::string get_iden_str() const =0;
        virtual std::string get_go_str() const { return get_iden_str() + " defeated!"; };
};