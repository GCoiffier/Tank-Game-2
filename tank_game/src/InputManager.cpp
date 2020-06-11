#include "InputManager.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

void InputManager::read_inputs(sf::Window& app){
    
    typedef sf::Keyboard::Key Key;
    typedef sf::Mouse::Button MouseB;
    constexpr auto p = sf::Keyboard::isKeyPressed;

    UP = p(Key::Z) || p(Key::Up);
    RIGHT = p(Key::D) || p(Key::Right);
    DOWN = p(Key::S) || p(Key::Down);
    LEFT = p(Key::Q) || p(Key::Left);
    MOUSE1 = sf::Mouse::isButtonPressed(MouseB::Left);

    *MOUSE_POS = sf::Mouse::getPosition(app);
}

InputManager USER_INPUTS;