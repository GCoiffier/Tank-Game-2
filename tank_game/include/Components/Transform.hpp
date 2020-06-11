#pragma once

#include <anax/Component.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <json.hpp>

struct TransformComponent : anax::Component {

    TransformComponent() = default;
    TransformComponent(const nlohmann::json&){}

    sf::Transformable transform;
};