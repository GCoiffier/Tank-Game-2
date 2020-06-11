#pragma once

#include <anax/Entity.hpp>
#include <anax/Component.hpp>
#include <iterator>
#include <vector>


/**
 * ChildrenComponent : a component used to store dependencies 
 *      between entities and build a scene graph
 * **/
struct ChildrenComponent : public anax::Component {

    void add_child(anax::Entity::Id _id) {
        children.push_back(_id);
    }

    void add_child(anax::Entity& _ent) {
        children.push_back(_ent.getId());
    }

    typedef std::vector<anax::Entity::Id>::iterator it;
    it begin() { return children.begin();}
    it end() { return children.end();} 

    std::vector<anax::Entity::Id> children;
};