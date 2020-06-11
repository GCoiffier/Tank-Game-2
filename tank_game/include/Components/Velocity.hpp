#pragma once

#include <anax/Component.hpp>
#include <json.hpp>
#include <SFML/System/Vector2.hpp>

struct VelocityComponent : anax::Component {

    VelocityComponent(float _speed=100)
    : 
        dir(1.0f, 0.f),
        currentSpeed(0.f),
        baseSpeed(_speed) 
    {}

    VelocityComponent(const nlohmann::json& j)
    :
        dir(1.0f, 0.f),
        currentSpeed(0.f)
    {
        baseSpeed = j["speed"].get<float>();
    }

    sf::Vector2f dir;
    float currentSpeed;
    float baseSpeed;
};