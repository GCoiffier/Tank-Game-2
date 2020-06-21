///
/// Example1
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#include "Level.hpp"
#include "common/macros.hpp"
#include "RessourceManager.hpp"
#include "InputManager.hpp"
#include "entity_init.hpp"

#include "Components.hpp"
#include "common/math.hpp"
#include "common/debug.hpp"

#include <iostream>
#include <memory>

#include <fstream>
#include <sstream>
#include <array>

constexpr unsigned int LEVEL_WIDTH = 40;
constexpr unsigned int LEVEL_HEIGHT = 25;

Level::Level(sf::RenderTarget& renderTarget)
: 
    is_debug(false),
    m_renderSystem(renderTarget),
    m_debugRenderSystem(renderTarget)
{
    m_world.addSystem(m_renderSystem);
    m_world.addSystem(m_debugRenderSystem);

    m_world.addSystem(m_shootSystem);
    m_world.addSystem(m_damageSystem);
    m_world.addSystem(m_controlSystem);
    m_world.addSystem(m_translationSystem);
    m_world.addSystem(m_rotationSystem);
    m_world.addSystem(m_animationSystem);
    m_world.addSystem(m_collisionSystem);    

    // create background
    anax::Entity bg = m_world.createEntity();
    auto& bgSprite = bg.addComponent<SpriteComponent>().sprite;
    bgSprite.setTexture(RM.get_texture("background.png"));
    auto bgTransform = bg.addComponent<TransformComponent>().transform;
    bg.activate();

    // create world borders
    auto initBorder = [&](const float& x, const float& y, const float& w, const float& h) {
        anax::Entity wall = m_world.createEntity();
        wall.addComponent<TypeComponent>(EntityType::OBSTACLE);
        auto& colli = wall.addComponent<CollisionComponent>();
        colli.boundingBox = {0, 0, w, h};
        auto& transform = wall.addComponent<TransformComponent>().transform;
        transform.setPosition(sf::Vector2f(x, y));
        wall.activate();
    };

    sf::Vector2u levelSize = renderTarget.getSize();
    FOR(i, LEVEL_WIDTH) {
        initBorder(32*i, -32, 32, 32);
        initBorder(32*i, 32*LEVEL_HEIGHT, 32, 32);
    }

    FOR(j, LEVEL_HEIGHT) {
        initBorder(-32, 32*j, 32, 32);
        initBorder(32*LEVEL_WIDTH, 32*j, 32, 32);
    } 
}


void Level::load_from_file(const std::string& level_name){    
    std::string path = "../static/levels/" + level_name + ".json";
    load_level_from_file(m_world, path);
}


void Level::update(float deltaTime) {
    m_world.refresh();

    m_controlSystem.update(deltaTime);
    m_animationSystem.update(deltaTime);
    m_translationSystem.update(deltaTime);
    m_rotationSystem.update(deltaTime);
    m_collisionSystem.update(deltaTime);
    m_shootSystem.update(deltaTime);
    m_damageSystem.update(deltaTime);
}

void Level::render() {
    m_renderSystem.render();
    if (is_debug) {
        m_debugRenderSystem.render();
    }
}

void Level::handleEvents(sf::Event event) {
    switch(event.type) {
        case sf::Event::Closed:
            quit();
            break;
        case sf::Event::KeyPressed: {
            switch(event.key.code) {
                case sf::Keyboard::Key::Escape:
                    quit();
                    break;
                case sf::Keyboard::Key::A:{
                    is_debug = !is_debug;
                    is_debug ? plop("DEBUG TRUE") : plop("DEBUG FALSE");
                    break;
                }
                default:
                    break;
            }
            break;
        }

        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Button::Left){
                m_controlSystem.handleMouseClick();
            }
            break;
        }

        default:
            break;
    }
}