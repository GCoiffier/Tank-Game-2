#pragma once

#include <Components/Shoot.hpp>
#include <anax/System.hpp>

struct ShootSystem :
    public anax::System< anax::Requires<ShootComponent>>
{
    void update(double);
};