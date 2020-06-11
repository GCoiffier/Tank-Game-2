#include "entity_init.hpp"
#include "Components.hpp"

#include "RessourceManager.hpp"
#include "InputManager.hpp"

#include "common/debug.hpp"
#include "common/math.hpp"

#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <exception>
#include <vector>

using json = nlohmann::json;

static const std::string TEMPLATE_PATH = "../static/templates/";

anax::Entity::Id load_entity_from_json(anax::World& world, json& j) {
    anax::Entity e;
    do {
        e = world.createEntity();
    }   while (!e.isValid());

    plop(j["name"].get<std::string>());

    // TypeComponent
    if (j.contains("type")) {
        e.addComponent<TypeComponent>(j["type"]);
    } else {
        e.addComponent<TypeComponent>(EntityType::DEFAULT);
    }

    // SpriteComponent
    if (j.contains("sprite")) e.addComponent<SpriteComponent>(j["sprite"]);

    // AnimationComponent
    if (j.contains("animation")) e.addComponent<AnimationComponent>(j["animation"]);

    // TransformComponent
    if (j.contains("transform")) e.addComponent<TransformComponent>(j["transform"]);

    // VelocityComponent
    if (j.contains("velocity")) e.addComponent<VelocityComponent>(j["velocity"]);

    // CollisionComponent
    if (j.contains("collision")) e.addComponent<CollisionComponent>(j["collision"]);

    // OrientationComponent
    if (j.contains("orientation")) e.addComponent<OrientationComponent>(j["orientation"]);

    // ShootComponent
    if (j.contains("shoot")) e.addComponent<ShootComponent>(j["shoot"]);

    // DamageComponent
    if (j.contains("damage"))  e.addComponent<DamageComponent>(j["damage"]);

    // DebugComponent
    if (j.contains("debug")) e.addComponent<DebugComponent>(j["debug"]); 

    // ControlComponent
    if (j.contains("control")) e.addComponent<ControlComponent>(j["control"]);

    // ChildrenComponent
    if (j.contains("children")) {
        auto& children = e.addComponent<ChildrenComponent>();
        for (auto& jchild : j["children"]) {
            anax::Entity::Id child_id;
            if (jchild.contains("template")) {
                std::string path = jchild["template"].get<std::string>();
                child_id = load_entity_from_file(world, path);
            } else {
                child_id = load_entity_from_json(world, jchild);
            }
            children.add_child(child_id);
        }
    }

    e.activate();
    return e.getId();
}


anax::Entity::Id load_entity_from_file(anax::World& world, const std::string& fileName){
    try {
        json data;
        std::ifstream strm(TEMPLATE_PATH+fileName);
        strm >> data;
        strm.close();
        return load_entity_from_json(world, data);
    } catch (std::exception& e) {
        std::cerr << "ERROR when loading file '" << fileName << "'" << std::endl;
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void load_level_from_json(anax::World& world, json& root){

    for(auto& [path, json] : root.items()){
        for (auto& jsonPos : json["position"]){
            std::vector<float> _pos = jsonPos.get<std::vector<float>>();
            sf::Vector2f pos(32 * _pos[0] + 16, 32 * _pos[1] + 16);
            anax::Entity::Id id = load_entity_from_file(world, path);
            anax::Entity created = world.getEntity(id.index);
            auto& transform = created.getComponent<TransformComponent>().transform;
            transform.setPosition(pos);
            if (created.hasComponent<ChildrenComponent>()) { // Also translate children entities
                for (auto& id_child : created.getComponent<ChildrenComponent>()) {
                    const anax::Entity& child = world.getEntity(id_child.index);
                    if (child.hasComponent<TransformComponent>()){
                        auto& childTransform = child.getComponent<TransformComponent>().transform;
                        childTransform.setPosition(pos);
                    }
                }
            }
        }
    }
}

void load_level_from_file(anax::World& world, const std::string& fileName){
    json data;
    std::ifstream strm(fileName);
    strm >> data;
    strm.close();
    return load_level_from_json(world, data);
}