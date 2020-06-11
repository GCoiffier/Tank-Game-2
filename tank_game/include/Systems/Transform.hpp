#pragma once

#include <anax/System.hpp>

#include <Components/Transform.hpp>
#include <Components/Orientation.hpp>
#include <Components/Velocity.hpp>


struct TranslationSystem : 
    anax::System<
        anax::Requires<TransformComponent, VelocityComponent>>
{
    TranslationSystem() = default;
    void update(double deltaTime);
};



struct RotationSystem : 
    anax::System<
        anax::Requires<TransformComponent, OrientationComponent>>
{
    RotationSystem() = default;
    void update(double deltaTime);
};