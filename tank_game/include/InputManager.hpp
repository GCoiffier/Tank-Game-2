#pragma once

#include <SFML/Window.hpp>

#include <memory>

struct InputManager {

    InputManager() {
        MOUSE_POS = std::make_shared<sf::Vector2i>(0,0);
    }

    void read_inputs(sf::Window&);

    bool UP;
    bool RIGHT;
    bool DOWN;
    bool LEFT;
    bool MOUSE1;

    std::shared_ptr<sf::Vector2i> MOUSE_POS;
};

extern InputManager USER_INPUTS;