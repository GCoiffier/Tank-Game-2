#pragma once

#include "Components/Damage.hpp"
#include <anax/System.hpp>

struct DamageSystem :
    anax::System<
        anax::Requires<DamageComponent>>
{
    void update(double deltaTime);
};