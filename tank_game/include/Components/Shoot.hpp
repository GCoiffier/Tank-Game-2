#pragma once

#include <json.hpp>
#include <anax/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <queue>

enum class BulletType {
    CLASSIC = 0,
    FAST = 1,
    GUIDED = 2,
    FRAGMENT = 3,
    EGG = 42,
    THANOS = 69
};

NLOHMANN_JSON_SERIALIZE_ENUM( BulletType, {
    { BulletType::CLASSIC, "classic"},
    { BulletType::FAST, "fast"},
    { BulletType::GUIDED, "guided"},
    { BulletType::FRAGMENT, "fragment"},
    { BulletType::THANOS, "thanos"},
    { BulletType::EGG, "egg"}
})

struct ShootParameters {
    sf::Vector2f position;
    float angle;
};

struct ShootComponent : anax::Component {
    
    ShootComponent(const BulletType& _type = BulletType::CLASSIC) 
    : 
        type(_type) 
    {}

    ShootComponent(const nlohmann::json& j){
        type = j["bullet_type"].get<BulletType>();
    }

    BulletType type;
    std::queue<ShootParameters> queue;
};