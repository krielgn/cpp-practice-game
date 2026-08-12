#include <cstdlib>

#include "action.h"
#include "actor.h"
#include "helper.h"

Action::Action(std::string n, AType t, int c){
    _name = n;
    _type = t;
    _cost = c;
}

Attack::Attack(std::string n, int dam, int ch, int pi, int co)
: Action::Action(n, AType::ATTACK, co) {
    _damage = dam;
    _chance = ch;
    _pierce = pi;
}

Heal::Heal(std::string n, Heal::HealType ht, int ha, int co) 
: Action::Action(n, AType::HEAL, co) {
    _heal = ha;
    _hType = ht;
    _targets_player = true;
}

Mod::Mod(std::string n, std::string sn, int dur, int num, ModVar var, AType type, int co)
: Action::Action(n, type, co) {
    _status_name = sn;
    _duration = dur;
    _mod_num = num;
    _mod_var = var;
}

BuffAction::BuffAction(std::string n, std::string sn, int dur, int num, ModVar var, int co)
: Mod::Mod(n, sn, dur, num, var, AType::BUFF, co) { 
    _targets_player = true;
}

DebuffAction::DebuffAction(std::string n, std::string sn, int dur, int num, ModVar var, int co)
: Mod::Mod(n, sn, dur, num, var, AType::DEBUFF, co) { }

void Attack::perform(Actor& src, Actor& tgt) {
    delay_msg_nn(_name + "... ");
    int total_chance = _chance + src.get_mod_num_total(ModVar::TO_HIT);
    src.spend_cost(get_cost());

    if (rand() % 100 <= total_chance){
        delay_msg_nn("hits!");

        int dam = calc_full_damage(src, tgt);

        delay_msg(" And deals " + std::to_string(dam) + " damage!");

        tgt.apply_damage(dam);
    } else {
        delay_msg("misses!");
    }
}

int Attack::calc_full_damage(Actor& src, Actor& tgt) {
    int def = tgt.get_defense() + tgt.get_mod_num_total(ModVar::DEF);
    int pierce = get_pierce() + src.get_mod_num_total(ModVar::PIERCE);

    return get_damage() - (def - pierce);
}

void Heal::perform(Actor& src, Actor& tgt) {
    tgt.apply_heal(*this);
    delay_msg(tgt.get_name() + " recovered " + get_type_string());
}

void Mod::perform(Actor& src, Actor& tgt) {
    int index = tgt.has_status(_status_name);
    src.spend_cost(get_cost());

    if (index == -1) {
        delay_msg(tgt.get_iden_str() + " now: " + _status_name);
        tgt.apply_status(make_status_obj());
    } else {
        delay_msg(tgt.get_iden_str() + " more: " + _status_name);
        tgt.extend_status(index, _duration);
    }
}