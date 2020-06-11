#pragma once

#include "RessourceManager.hpp"

#include <anax/Component.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <json.hpp>

struct SpriteComponent : anax::Component {
    SpriteComponent(int _z=0) : z(_z) {}

    SpriteComponent(const nlohmann::json& j) {
        z = j["z"].get<int>();
        sprite.setTexture(RM.get_texture(j["name"]));
        sprite.setOrigin(j["origin"][0], j["origin"][1]);
    }

    sf::Sprite sprite;
    int z;
};