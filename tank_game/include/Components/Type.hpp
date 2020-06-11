#pragma once

#include <anax/Component.hpp>
#include <json.hpp>

enum class EntityType {
    DEFAULT=0,
    TANK=1,
    TURRET=2,
    OBSTACLE=4,
    BULLET=5
};

NLOHMANN_JSON_SERIALIZE_ENUM( EntityType, {
    { EntityType::DEFAULT, nullptr},
    { EntityType::TANK, "tank"},
    { EntityType::TURRET, "turret"},
    { EntityType::OBSTACLE, "obstacle"},
    { EntityType::BULLET, "bullet"}
})


struct TypeComponent : anax::Component {

    TypeComponent() : type(EntityType::DEFAULT) {}
    TypeComponent(const EntityType _type) : type(_type) {}
    TypeComponent(const nlohmann::json& j) {
        type = j.get<EntityType>();
    }

    EntityType type;
};

