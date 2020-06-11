#pragma once

#include <json.hpp>
#include <anax/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>


struct OrientationComponent : anax::Component {

    OrientationComponent(float _baseSpeed=0.f)
    : 
        angle(0.f), 
        baseSpeed(_baseSpeed), 
        currentSpeed(0.f) 
    {};

    OrientationComponent(const nlohmann::json& j)
    :
        currentSpeed(0.f)
    {
        angle = j["angle"].get<float>();
        baseSpeed = j["speed"].get<float>();
    }
    
    float angle;
    float baseSpeed;
    float currentSpeed;
};