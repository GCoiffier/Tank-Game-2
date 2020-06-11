#pragma once
#include <json.hpp>
#include <anax/Component.hpp>

struct DamageComponent : anax::Component {

    DamageComponent(int _hp=1) : hp(_hp), dmgAcc(0) {}
     
    DamageComponent(const nlohmann::json& j) 
    :
        dmgAcc(0)
    {
        hp = j["hp"].get<int>();
    }

    int hp; // number of health points
    int dmgAcc; // an accumulator for damages received
};