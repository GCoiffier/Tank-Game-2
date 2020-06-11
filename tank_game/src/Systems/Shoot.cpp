#include "Systems/Shoot.hpp"

#include "Components/Transform.hpp"
#include "Components/Velocity.hpp"

#include "entity_init.hpp"
#include "common/debug.hpp"
#include "common/math.hpp"

static void setup_bullet(anax::Entity& bullet, const sf::Vector2f& pos, const float angle){
    auto& transform = bullet.addComponent<TransformComponent>().transform;
    transform.setPosition(pos);
    transform.rotate(angle - 90.f);
    auto& vel = bullet.getComponent<VelocityComponent>();
    rotate(vel.dir, 90.f - angle);
    vel.currentSpeed = vel.baseSpeed;
}

void ShootSystem::update(double){
    anax::World& world = getWorld();
    for (auto& entity : getEntities()){
        auto& shoot = entity.getComponent<ShootComponent>();
        while (!shoot.queue.empty()){
            ShootParameters& p = shoot.queue.front();
            anax::Entity::Id id_bullet;
            switch (shoot.type) {
            case BulletType::CLASSIC :
                id_bullet = load_entity_from_file(world, "bullets/bullet_classic.json");
                break;
            case BulletType::FAST :
                id_bullet = load_entity_from_file(world, "bullets/bullet_fast.json");
                break;
            case BulletType::EGG :
                id_bullet = load_entity_from_file(world, "bullets/egg.json");
                break;                
            default:
                break;
            }

            // Set position and orientation of bullet
            auto e = world.getEntity(id_bullet.index);
            setup_bullet(e, p.position, p.angle);
            shoot.queue.pop();
        }
    }
}