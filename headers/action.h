#pragma once

#include <string>
#include <memory>

#include "status.h"

class Actor;

class Action {
    public:
        enum AType {ATTACK, BUFF, DEBUFF, HEAL};

    protected:
        AType _type;
        std::string _name;
        int _cost;
        bool _targets_player = false;

    public:
        std::string get_name() const { return _name; }
        AType get_type() const { return _type; }
        int get_cost() const { return _cost; }
        bool get_targets_player() const { return _targets_player; }

        virtual void perform(Actor& src, Actor& tgt) =0;

        Action(std::string n, AType t, int c);
        
};

class Attack : public Action {

     int _damage;
     int _chance;
     int _pierce;

     public:
         int get_chance() const { return _chance; }
         int get_damage() const { return _damage; }
         int get_pierce() const { return _pierce; }

         void perform(Actor& src, Actor& tgt) override;
         int calc_full_damage(Actor& src, Actor& tgt);

         Attack(std::string n, int def, int ch = 100, int pi = 0, int co = 0);

};

class Heal : public Action {
    public:
        enum HealType { HP, MP};
    
    protected:
        int _heal;
        HealType _hType;

    public:
        int get_heal() const { return _heal; }
        HealType get_heal_type() const { return _hType; }
        void perform(Actor& src, Actor& tgt) override;
        std::string get_type_string() const { if (_hType == HealType::HP) { return "HP"; } else { return "SP"; }}

        Heal(std::string n, HealType ht, int ha, int co=0);
};

class Mod : public Action {
    protected:
        std::string _status_name;
        int _duration;
        int _mod_num;
        ModVar _mod_var;

    public:
        Mod(std::string n, std::string sn, int dur, int num, ModVar var, AType type, int co);
        
        std::string get_status_name() const { return _status_name; }
        virtual void perform(Actor& src, Actor& tgt);

        auto make_status_obj() const { return Status(_status_name, _duration, _mod_num, _mod_var); }
};

class BuffAction : public Mod {

    public:
        BuffAction(std::string n, std::string sn, int dur, int num, ModVar var, int co);

};

class DebuffAction : public Mod { 

    public:
        DebuffAction(std::string n, std::string sn, int dur, int num, ModVar var, int co);
};

