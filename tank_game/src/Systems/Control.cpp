#include "Systems/Control.hpp"

#include "common/debug.hpp"
#include "common/math.hpp"

#include "InputManager.hpp"
#include "Components.hpp"

#include <anax/World.hpp>

#include <cmath>
#include <exception>

ControlSystem::ControlSystem() : m_mouseButtonPressed(false) {}

static const anax::Entity get_turret(anax::Entity& e){
    for (const anax::Entity::Id& id : e.getComponent<ChildrenComponent>()){
        const anax::Entity turret = e.getWorld().getEntity(id.index);
        if (turret.getComponent<TypeComponent>().type == EntityType::TURRET){
            return turret;
        }
    }
    throw std::exception();
}

void ControlSystem::update(double deltaTime) {
    auto entities = getEntities();
    for (auto e : entities) {
        auto& vel = e.getComponent<VelocityComponent>();
        auto& orient = e.getComponent<OrientationComponent>();

        // 1/ Update of tank body using keys
        vel.currentSpeed = 0.f;
        orient.currentSpeed = 0.f;

        if (USER_INPUTS.UP)     vel.currentSpeed += vel.baseSpeed;
        if (USER_INPUTS.DOWN)   vel.currentSpeed -= vel.baseSpeed;

        if (USER_INPUTS.LEFT || USER_INPUTS.RIGHT){
            vel.currentSpeed /= 2;
        }

        if (USER_INPUTS.RIGHT)  orient.currentSpeed += orient.baseSpeed;
        if (USER_INPUTS.LEFT)   orient.currentSpeed -= orient.baseSpeed;

        float angle =  - deltaTime * orient.currentSpeed;
        rotate(vel.dir, angle);

        // 2/ Update of tank turret using mouse position
        const anax::Entity turret = get_turret(e);
        auto& turretOrient = turret.getComponent<OrientationComponent>();
        auto& turretTransform = turret.getComponent<TransformComponent>().transform;

        sf::Vector2f turretPos = turretTransform.getPosition();
        sf::Vector2f targetPos = sf::Vector2f(*USER_INPUTS.MOUSE_POS);
                            
        float dx = targetPos.x - turretPos.x;
        float dy = turretPos.y - targetPos.y;
        float new_angle = 180.0f * atan2(dx,dy) / M_PI;

        turretTransform.rotate(new_angle - turretOrient.angle + angle);
        turretOrient.angle = new_angle;

        // 3/ Check if the player wants to shoot
        if (m_mouseButtonPressed){
            m_mouseButtonPressed = false;
            if (e.hasComponent<ShootComponent>()) {
                auto& queue = e.getComponent<ShootComponent>().queue;
                ShootParameters params;
                params.position = turretPos + 30.f * (targetPos - turretPos)/ norm(targetPos - turretPos);
                params.angle = turretOrient.angle;
                queue.push(params);
            }
        }
    }
}


void ControlSystem::handleMouseClick(){
    m_mouseButtonPressed = true;
}