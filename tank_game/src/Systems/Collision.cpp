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

#include <Systems/Collision.hpp>
#include "Components.hpp"

#include "common/debug.hpp"
#include "common/math.hpp"

#include <anax/World.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

static sf::FloatRect getBBoxRect(const sf::Transformable& transformable, const sf::FloatRect& bbox) {
    return sf::FloatRect(transformable.getPosition().x + bbox.left, transformable.getPosition().y + bbox.top, bbox.width, bbox.height);
}

static sf::FloatRect getBBoxRect(const anax::Entity& entity) {
    auto& transform = entity.getComponent<TransformComponent>().transform;
    auto& bbox = entity.getComponent<CollisionComponent>().boundingBox;
    return getBBoxRect(transform, bbox);
}

static void collision_debug(const anax::Entity& e){
    auto& transform = e.getComponent<TransformComponent>().transform;
    auto& bbox = e.getComponent<CollisionComponent>().boundingBox;
    sf::Vector2f size(bbox.width, bbox.height);
    sf::Vector2f position(transform.getPosition());
    position.x += bbox.left;
    position.y += bbox.top;

    sf::VertexArray rect(sf::Quads, 4);
    for (unsigned int i=0 ; i<4 ; i++){
        rect[i].position = position;
        rect[i].color = sf::Color(0, 0, 255, 100);
    }
    rect[1].position.x += size.x;
    rect[2].position += size;
    rect[3].position.y += size.y;
    e.getComponent<DebugComponent>().map["hitbox"] = rect;
}

void CollisionSystem::update(double deltaTime)
{
    auto colliders = getEntities();

    // Temporary values for rectangles (to check collision)
    sf::FloatRect rect1;
    sf::FloatRect rect2;	

    for(std::size_t i = 0; i < colliders.size(); ++i) {
        auto& e1 = colliders[i];
        for(std::size_t j = i+1; j < colliders.size(); ++j) {
            auto& e2 = colliders[j];
            if (!e1.getComponent<CollisionComponent>().causesEvents && 
                !e2.getComponent<CollisionComponent>().causesEvents) {
                continue;
            }

            rect1 = getBBoxRect(e1);
            rect2 = getBBoxRect(e2);
            // Check for the collision
            if(rect1.intersects(rect2)) {
                onCollisionOccured(e1, e2, deltaTime);
            }
        }

        if (e1.hasComponent<DebugComponent>()) collision_debug(e1);
    }
}

void CollisionSystem::onCollisionOccured(anax::Entity& e1, anax::Entity& e2, double deltaTime) {
    
    if (e1.hasComponent<ControlComponent>()){
        handleCollisionPlayer(e1, e2, deltaTime);
    } else if (e2.hasComponent<ControlComponent>()){
        handleCollisionPlayer(e2, e1, deltaTime);
    }

    auto type1 = e1.getComponent<TypeComponent>().type;
    auto type2 = e2.getComponent<TypeComponent>().type;

    if (type1 == EntityType::BULLET){
        handleCollisionBullet(e1, e2, deltaTime);
    } else if (type2 == EntityType::BULLET){
        handleCollisionBullet(e2, e1, deltaTime);
    }
}


void CollisionSystem::handleCollisionBullet(anax::Entity& bullet, anax::Entity& collided, double) {
    bullet.kill();
    plop("bullet killed");
    if (collided.hasComponent<DamageComponent>()){
        collided.getComponent<DamageComponent>().dmgAcc++;
    }
}

void CollisionSystem::handleCollisionPlayer(anax::Entity& player, anax::Entity& collided, double deltaTime) {
    
    auto& world = player.getWorld();

    auto move = [&](anax::Entity& e, sf::Vector2f vec){
        auto& transform = e.getComponent<TransformComponent>().transform;
        transform.move(vec);
        for (const anax::Entity::Id& id : e.getComponent<ChildrenComponent>()) {
            auto& childTransform = world.getEntity(id.index).getComponent<TransformComponent>().transform;
            childTransform.move(vec);
        }
    };

    auto dFilter = [](float d) {
        if (d>=0) return std::max(0.f, (d - 0.2f));
        return std::min(0.f, d+0.2f);
    };

    // Cancel movement of the player
    auto& velocity = player.getComponent<VelocityComponent>();
    const float dv = float(velocity.currentSpeed * deltaTime);
    move(player, (-dv) * velocity.dir);

    sf::FloatRect rp = getBBoxRect(player);
    sf::FloatRect ro = getBBoxRect(collided);

    sf::Vector2f proj( rp.left + rp.width/2 - ro.left - ro.width/2,
                      rp.top + rp.height/2 - ro.top - ro.height/2); // center to center vector
    proj /= norm(proj);
    float d = dot(proj, velocity.dir);
    if ((d > 0 && velocity.currentSpeed>0) || (d < 0 && velocity.currentSpeed < 0)) {
        move(player, (dv * d) * proj);
    }
    rotate(proj, 90.f);
    d = dot(proj, velocity.dir);
    move(player, (dv * dFilter(d)) * proj);
}