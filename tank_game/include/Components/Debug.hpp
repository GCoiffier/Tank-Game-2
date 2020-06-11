#pragma once

#include <json.hpp>
#include <anax/Component.hpp>

#include <SFML/Graphics/Shape.hpp>
#include <map>
#include <string>

struct DebugComponent : public anax::Component {

    DebugComponent() = default;
    DebugComponent(const nlohmann::json&) {}

    std::map<std::string, sf::VertexArray> map;

};