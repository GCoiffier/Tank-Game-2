#include "Systems/Transform.hpp"
#include <anax/World.hpp>

#include <Components/Control.hpp> // Debug
#include <Components/Children.hpp>
#include <Components/Debug.hpp>
#include "common/debug.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>

void TranslationSystem::update(double deltaTime) {
    auto entities = getEntities();
    for(auto& entity : entities) {
        auto& transform = entity.getComponent<TransformComponent>().transform;        
        auto& velocity = entity.getComponent<VelocityComponent>();

        sf::Vector2f vel = velocity.currentSpeed * (float)deltaTime * velocity.dir;
        transform.move(vel);

        // Also translate children entities
        if (entity.hasComponent<ChildrenComponent>()) {
            for (auto& id : entity.getComponent<ChildrenComponent>()) {
                const anax::Entity& child = getWorld().getEntity(id.index);
                if (child.hasComponent<TransformComponent>()){
                    auto& childTransform = child.getComponent<TransformComponent>().transform;
                    childTransform.move(vel);
                }
            }
        }

        // Debug display for translation
        if (entity.hasComponent<DebugComponent>()){
            auto& debug = entity.getComponent<DebugComponent>();
            sf::VertexArray line(sf::Lines, 2);
            line[0].color = sf::Color::Red;
            line[0].position = transform.getPosition();
            line[1].color = sf::Color::Red;
            line[1].position = transform.getPosition() + velocity.baseSpeed * velocity.dir;
            debug.map["velocity"] = line;
        }   
    }
}



void RotationSystem::update(double deltaTime) {
    auto entities = getEntities();
    for(auto& entity : entities) {
        auto& transform = entity.getComponent<TransformComponent>().transform;
        auto& orient = entity.getComponent<OrientationComponent>();
        float angl = deltaTime * orient.currentSpeed;
        transform.rotate(angl);
        orient.angle += angl;

        // Also translate children entities
        if (entity.hasComponent<ChildrenComponent>()) {
            for (auto& id : entity.getComponent<ChildrenComponent>()) {
                const anax::Entity& child = getWorld().getEntity(id.index);
                if (child.hasComponent<TransformComponent>()){
                    auto& childTransform = child.getComponent<TransformComponent>().transform;
                    childTransform.rotate(angl);
                }
            }
        }
    }
}