#pragma once

#include "RessourceManager.hpp"

#include <anax/Component.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <json.hpp>
#include <string>

/* Information required to initialize a SpriteComponent */
struct SpriteInitComponent : anax::Component {

    SpriteInitComponent(const nlohmann::json& j) {
        z = j["z"].get<int>();
        spriteName = j["name"].get<std::string>();
        origin.x = j["origin"][0];
        origin.y = j["origin"][1];
    }

    std::string spriteName;
    int z;
    sf::Vector2f origin;
};

/* A sprite Component */
struct SpriteComponent : anax::Component {
    SpriteComponent(int _z=0) : z(_z) {}

    SpriteComponent(const SpriteInitComponent& init){
        z = init.z;
        sprite.setTexture(RM.get_texture(init.spriteName));
        sprite.setOrigin(init.origin.x, init.origin.y);
    }

    SpriteComponent(const nlohmann::json& j) {
        z = j["z"].get<int>();
        sprite.setTexture(RM.get_texture(j["name"]));
        sprite.setOrigin(j["origin"][0], j["origin"][1]);
    }
    sf::Sprite sprite;
    int z;
};