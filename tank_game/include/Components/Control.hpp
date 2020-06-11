#pragma once

#include <json.hpp>
#include <anax/Component.hpp>
#include <anax/Entity.hpp>

struct ControlComponent : anax::Component {
    ControlComponent() = default;
    ControlComponent(const nlohmann::json&) {}
};