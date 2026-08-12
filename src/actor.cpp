#include <iostream>

#include "actor.h"
#include "helper.h"

Actor::Actor(int hp, int mp, int def) {
    _maxHP = _HP = hp;
    _maxMP = _MP = mp;
    _defense = def;
}

void Actor::add_move(std::unique_ptr<Action> act) {
    _moves.push_back(std::move(act));
}

std::vector<Action*> Actor::get_moves() const {
    std::vector<Action*> test = {};
    for (int i = 0; i < _moves.size(); i++) {
        test.push_back(get_move(i));
    }
    return test;
}

int Actor::get_mod_num_total(ModVar var) const {
    int total_mod = 0;
    for (auto it = _status.begin(); it != _status.end(); ){
        if (it->get_var() == var){
            total_mod += it->get_num();
        }
        it++;
    }
    return total_mod;
}


void Actor::apply_damage(int damage) {
    _HP -= damage;

    if (_HP <= 0){
        delay_msg(get_go_str());
    }    
}

void Actor::apply_heal(Heal& h){
    int* v;
    int* vMax;
    if (h.get_heal_type() == Heal::HealType::HP) {
        v = &_HP;
        vMax = &_maxHP;
    } else {
        v = &_MP;
        vMax = &_maxMP;
    }
    *v += h.get_heal();
    if (*v > *vMax){
        *v = *vMax;
    }
}

void Actor::apply_status(Status status) {
    _status.push_back(status);
}

void Actor::extend_status(int index, int dur) {
    _status[index].extend_duration(dur);
}

int Actor::has_status(std::string name) const {
    for (int i = 0; i < _status.size(); i++) {
        if (_status[i].get_name() == name){
            return i;
        }
    }
    return -1;
}

void Actor::perform(int index){
    Action* act = get_move(index);
    Actor* target;
    if (act->get_targets_player()){
        target = this;
    } else {
        target = get_opponent();
    }

    act->perform(*this, *target);
}

void Actor::turn_done(){
    for (auto it = _status.begin(); it != _status.end(); ){
        bool keep = it->decrease_duration();
        if (keep){
            it++;
        } else {
            std::cout << get_name() << " is no longer " << it->get_name() << "!\n";
            it = _status.erase(it);
        }
    }
}