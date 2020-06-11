#pragma once

#include <vector>

#include <anax/System.hpp>
#include <Components/Sprite.hpp>
#include <Components/Animation.hpp>

struct AnimationSystem :
    anax::System<
        anax::Requires<SpriteComponent, AnimationComponent>>
{
    void update(double deltaTime);
};