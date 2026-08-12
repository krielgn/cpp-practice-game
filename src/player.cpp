#include <iostream>
#include <vector>

#include "player.h"
#include "helper.h"

Player::Player(int hp, int mp, int def)
: Actor::Actor(hp, mp, def) {
    _name = "Player";
}

/*void Player::add_inv(Item item) {
    _inventory.push_back(item);
}

void Player::print_inv() const {
    for (auto i: _inventory) {
        std::cout << i.get_name();
        if (i.get_id() != _inventory.back().get_id()){
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}*/

void Player::print_start_turn() const {
    delay_msg("Your Turn!");
    delay_msg_nn("HP: " + std::to_string(_HP) + "/" + std::to_string(_maxHP));
    delay_msg("        SP: " + std::to_string(_MP) + "/" + std::to_string(_maxMP));
    delay_msg("");
}