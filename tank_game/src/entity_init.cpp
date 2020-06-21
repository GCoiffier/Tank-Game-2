#include "entity_init.hpp"
#include "Components.hpp"

#include "RessourceManager.hpp"
#include "InputManager.hpp"
#include "tiles.hpp"

#include "common/debug.hpp"
#include "common/math.hpp"
#include "common/grid.hpp"
#include "common/macros.hpp"

#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <exception>
#include <vector>

using json = nlohmann::json;

static const std::string TEMPLATE_PATH = "../static/templates/";

void load_entity_from_json(anax::Entity& e, json& j, bool connect_adjacent) {

    // TypeComponent
    if (j.contains("type")) {
        e.addComponent<TypeComponent>(j["type"]);
    } else {
        e.addComponent<TypeComponent>(EntityType::DEFAULT);
    }

    // SpriteComponent
    if (j.contains("sprite")) {
        if (connect_adjacent){
            // Register initialization for later
            e.addComponent<SpriteInitComponent>(j["sprite"]);
        } else {
            // Init SpriteComponent normally
            e.addComponent<SpriteComponent>(j["sprite"]);
        }
    }

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
            anax::Entity child = e.getWorld().createEntity();
            if (jchild.contains("template")) {
                std::string path = jchild["template"].get<std::string>();
                load_entity_from_file(child, path);
            } else {
                load_entity_from_json(child, jchild);
            }
            children.add_child(child.getId());
            child.activate();
        }
    }
}


void load_entity_from_file(anax::Entity& e, const std::string& fileName, bool connect_adjacent){
    try {
        json data;
        std::ifstream strm(TEMPLATE_PATH+fileName);
        strm >> data;
        strm.close();
        load_entity_from_json(e, data, connect_adjacent);
    } catch (std::exception& excp) {
        std::cerr << "ERROR when loading file '" << fileName << "'" << std::endl;
        std::cerr << excp.what() << std::endl;
        throw excp;
    }
}

void load_level_from_json(anax::World& world, json& root){

    Grid<anax::Entity> tileMap(40, 25);
    for(auto& [path, json] : root.items()) {

        // Initialize one type of entities at each specified positions
        tileMap.clear();

        const bool connect_adjacent = json.contains("connect_adjacent") && json["connect_adjacent"].get<bool>();

        for (auto& jsonPos : json["position"]){
            std::vector<int> pos = jsonPos.get<std::vector<int>>();
            sf::Vector2f pixel_pos(32 * pos[0] + 16, 32 * pos[1] + 16);

            anax::Entity e = world.createEntity();
            load_entity_from_file(e, path, connect_adjacent);
            tileMap(pos[0], pos[1]) = e;

            auto& transform = e.getComponent<TransformComponent>().transform;
            transform.setPosition(pixel_pos);
            if (e.hasComponent<ChildrenComponent>()) { // Also translate children entities
                for (auto& id_child : e.getComponent<ChildrenComponent>()) {
                    const anax::Entity& child = world.getEntity(id_child.index);
                    if (child.hasComponent<TransformComponent>()){
                        auto& childTransform = child.getComponent<TransformComponent>().transform;
                        childTransform.setPosition(pixel_pos);
                    }
                }
            }
        }
        
        if (connect_adjacent){
            FOR2(i, j, tileMap.nb_lines(), tileMap.nb_cols()) {
                if (tileMap(i,j).isValid()){
                    int adjacent_code = encode_neighbours(tileMap, i, j);
                    anax::Entity e = tileMap(i,j);
                    auto& spriteInit = e.getComponent<SpriteInitComponent>();
                    spriteInit.spriteName = get_type(spriteInit.spriteName, adjacent_code);
                    plop(spriteInit.spriteName);
                    e.addComponent<SpriteComponent>(spriteInit);
                    e.removeComponent<SpriteInitComponent>();
                }
            }
        }

        FOR2(i, j,tileMap.nb_lines(), tileMap.nb_cols()){
            if (tileMap(i,j).isValid()) {
                tileMap(i,j).activate();
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