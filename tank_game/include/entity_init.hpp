#pragma once

#include <anax/World.hpp>
#include <anax/Entity.hpp>
#include <string>
#include <json.hpp>
#include <SFML/System/Vector2.hpp>

anax::Entity::Id load_entity_from_file(anax::World&, const std::string&);
anax::Entity::Id load_entity_from_json(anax::World&, nlohmann::json&);

void load_level_from_file(anax::World&, const std::string&);
void load_level_from_json(anax::World&, const nlohmann::json&);

void init_bullet(anax::Entity& bullet, const sf::Vector2f& initPos, const float angle, const float speed);