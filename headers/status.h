#pragma once
#include <string>

enum ModVar {TO_HIT, DEF, PIERCE};

class Status {
    std::string _name;
    int _duration;
    int _mod_num;
    ModVar _mod_var;

    public:
        Status(std::string name, int dur, int num, ModVar var) {
            _name = name;
            _duration = dur;
            _mod_num = num;
            _mod_var = var;
        }

        std::string get_name() const { return _name; }
        int get_num() const { return _mod_num; }
        ModVar get_var() const { return _mod_var; }

        void extend_duration(int dur) { _duration += dur; }
        bool decrease_duration(int i = 1) { 
            _duration -= i; 
            return _duration > 0;
        }

        /*friend std::ostream& operator<<(std::ostream& out, const Status& b) {
            out << b._name << " " << b._duration << " turns";
            return out;
        }*/

};