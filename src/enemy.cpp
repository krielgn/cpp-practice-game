#include <cstdlib>
#include <vector>

#include "enemy.h"

Enemy::Enemy(int hp, int mp, int def, std::string name)
: Actor::Actor(hp, mp, def) {
    _name = name;
}

void Enemy::choose_perform_action() {
    std::vector moves = get_valid_moves();

    if (_MP <= 3){
        moves.push_back(4);
    }
    
    int atk = rand() % moves.size();
    perform(moves[atk]);
}

std::vector<int> Enemy::get_valid_moves(){
    std::vector<int> out;

    for (int i = 0; i < _moves.size(); i++){
        auto mv = get_move(i);
        auto tp = mv->get_type();
        if (mv->get_cost() <= _MP && tp != Action::AType::HEAL){
            out.push_back(i);
        }
    }
    return out;
}