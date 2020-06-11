#pragma once

#include <SFML/Window.hpp>
#include <anax/World.hpp>
#include <cassert>

class Scene {
public:

    Scene() 
    : 
        m_isRunning(true)
    {}

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void handleEvents(sf::Event events) = 0;
    bool isRunning() const { return m_isRunning; }
    void quit() { m_isRunning = false; }

protected:

    anax::World m_world;
    bool m_isRunning;
};