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
            anax::Entity bullet;
            
            do {
                bullet = world.createEntity();
            }
            while (! bullet.isValid());

            switch (shoot.type) {
            case BulletType::CLASSIC :
                load_entity_from_file(bullet, "bullets/bullet_classic.json");
                break;
            case BulletType::FAST :
                load_entity_from_file(bullet, "bullets/bullet_fast.json");
                break;
            case BulletType::EGG :
                load_entity_from_file(bullet, "bullets/egg.json");
                break;                
            default:
                break;
            }

            // Set position and orientation of bullet
            setup_bullet(bullet, p.position, p.angle);
            bullet.activate();
            shoot.queue.pop();
        }
    }
}