#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cassert>

#include "helper.h"
#include "player.h"
#include "enemy.h"
//#include "item.h"

inline void initialize_actors(Player& p, Enemy& e) {
    p.set_opponent(e);
    e.set_opponent(p);

    //p.add_inv(Item(0, "shovel", Item::Type::GEAR));
    //p.add_inv(Item(1, "axe", Item::Type::GEAR));
    //p.add_inv(Item(2, "pick", Item::Type::GEAR));

    p.add_move(std::make_unique<Attack>("Bash", 3, 90));
    p.add_move(std::make_unique<Attack>("Stab", 4, 80, 0, 1));
    p.add_move(std::make_unique<Heal>("Heal", Heal::HealType::HP, 4, 2));
    p.add_move(std::make_unique<Heal>("Breather", Heal::HealType::MP, 5));
    p.add_move(std::make_unique<DebuffAction>("Flash", "Blinded", 2, -80, ModVar::TO_HIT, 3));
    p.add_move(std::make_unique<BuffAction>("Envigor", "Envigored", 4, 2, ModVar::PIERCE, 3));

    e.add_move(std::make_unique<Attack>("Stab", 3, 80, 0, 1));
    e.add_move(std::make_unique<Attack>("Shield Bash", 2, 95));
    e.add_move(std::make_unique<DebuffAction>("Trip", "Tripped", 1, -60, ModVar::TO_HIT, 2));
    e.add_move(std::make_unique<BuffAction>("Defensive Stance", "Defensive", 2, 2, ModVar::DEF, 2));
    e.add_move(std::make_unique<Heal>("Breather", Heal::HealType::MP, 4));
}

int player_turn_prompt(Player& p){
    int c = 0;
    int input = 0;
    bool valid = false;
    
    for (auto i: p.get_moves()){
        delay_msg_nn(std::to_string(c) + ": " + i->get_name());

        if (c % 2 != 0 && c > 0){
            std::cout << "\n";
        } else {
            for (int j = 0; j < 8 - i->get_name().size(); j++){
                std::cout << " ";
            }
        }
        c++;
    }
    delay_msg_nn("\n::");
    
    while (!valid){
        std::cin >> input;
         if (!std::cin) {
            std::cout << "INVALID!!\n::";
            std::cin.clear(); // Put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if (input >= 0 && input < p.get_moves().size()){
            if (p.get_move(input)->get_cost() > p.get_MP()){
                delay_msg("Not enough SP!");
            } else {
                valid = true;
            }            
        } else {
            std::cout << "Invalid input!!\n::";
        }
    }
    return input;
}

bool is_game_over(Player& p, Enemy& e){
    return p.is_dead() || e.is_dead();
}

int main(){
    //std::ios_base::sync_with_stdio(false);

    Player player = Player(10, 10, 0);
    Enemy enemy = Enemy(12, 10, 2, "Shieldman");
    initialize_actors(player, enemy);

    bool playerTurn = true;
    delay_msg_nn("Battle START!!! ");
    delay_msg("You are fighting: " + enemy.get_name());

    while (!is_game_over(player, enemy)){
        delay_msg("-------------");
        if (playerTurn) {
            player.print_start_turn();
            int act = player_turn_prompt(player);
            player.perform(act);
            player.turn_done();
        } else {
            delay_msg(enemy.get_name() + "'s Turn!");
            enemy.choose_perform_action();
            enemy.turn_done();
        }
        playerTurn = !playerTurn;
    }

    delay_msg("Game Over!", 80);
    int done;
    std::cin >> done;
    return 1;
}