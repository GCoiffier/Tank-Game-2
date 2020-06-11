
#pragma once

#include <anax/Component.hpp>
#include <json.hpp>
#include <SFML/Graphics/Rect.hpp>


struct CollisionComponent : anax::Component {

    CollisionComponent() : causesEvents(false) {}
    
    CollisionComponent(const nlohmann::json& j){
        causesEvents = j["causesEvents"].get<bool>();
        boundingBox = { 
            j["bbox"][0].get<float>(),
            j["bbox"][1].get<float>(),
            j["bbox"][2].get<float>(),
            j["bbox"][3].get<float>()
        };
    }

    sf::FloatRect boundingBox;
    bool causesEvents;
};
