///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#pragma once


#include "Tiles.hpp"
#include "Systems.hpp"
#include "Scene.hpp"

#include <SFML/Graphics.hpp>

#include <anax/anax.hpp>

#include <string>
#include <memory>

class Level :  public Scene {
public:

    /// Constructs the Game with a sf::RenderTarget
    /// \param renderTarget The sf::RenderTarget you wish to set the game up with
    Level(sf::RenderTarget&);
    void init();

    void load_from_file(const std::string&);
    
    void update(float deltaTime);
    void render();
    
    void handleEvents(sf::Event event);

private:
// ------ Methods ------

    void onCollisionOccured(anax::Entity& e1, anax::Entity& e2, double deltaTime);

// ------- Data -------
    bool is_debug;
    
    // Systems
    RenderSystem m_renderSystem;    
    DebugRenderSystem m_debugRenderSystem;    
    
    TranslationSystem m_translationSystem;
    RotationSystem m_rotationSystem;
    ControlSystem m_controlSystem;
    CollisionSystem m_collisionSystem;
    AnimationSystem m_animationSystem;
    ShootSystem m_shootSystem;
    DamageSystem m_damageSystem;
};