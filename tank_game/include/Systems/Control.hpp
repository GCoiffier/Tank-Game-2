#pragma once

#include <Components/Control.hpp>
#include <Components/Velocity.hpp>
#include <Components/Orientation.hpp>

#include <anax/System.hpp>

struct ControlSystem : 
    anax::System<anax::Requires<VelocityComponent, OrientationComponent, ControlComponent>>
{
public:
    ControlSystem();

    void update(double deltaTime);

    void handleMouseClick();

private:
    bool m_mouseButtonPressed;
};