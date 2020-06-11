#include "Systems/Damage.hpp"

#include "Components/Children.hpp"
#include "common/debug.hpp"

#include <anax/World.hpp>

static void recKill(anax::Entity& e){
    if (e.hasComponent<ChildrenComponent>()){
        for (auto& id : e.getComponent<ChildrenComponent>()){
            anax::Entity child = e.getWorld().getEntity(id.index);
            recKill(child);
        }
    }
    e.kill();
}

void DamageSystem::update(double){
    for (auto e : getEntities()) {
        auto& dmg = e.getComponent<DamageComponent>();
        dmg.hp -= dmg.dmgAcc;
        dmg.dmgAcc = 0;    
        if (dmg.hp<=0) {
            // entity has no health -> kill
            recKill(e);
        }
    }
}