#pragma once

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