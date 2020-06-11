#pragma once

#include <anax/Component.hpp>
#include <SFML/System/Vector2.hpp>

struct PositionComponent : anax::Component {

    PositionComponent() : pos(0.f, 0.f) {}
    PositionComponent(const sf::Vector2f& _pos) : pos(_pos) {}
    PositionComponent(const float& x, const float& y) : pos(x,y) {}

    sf::Vector2f pos;
};