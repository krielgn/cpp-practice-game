#pragma once
#include <string>

// Unused

class Item {
    public:
        enum Type { WEAPON, ARMOR, GEAR, CONSUM};

    private:
        int _ID;
        std::string _name;
        Type _type;

    public:        
        int get_id() const { return _ID; }
        std::string get_name() const { return _name; }
        Type get_type() const { return _type; }
        
        Item(int id, std::string name, Item::Type type);
        Item();
};