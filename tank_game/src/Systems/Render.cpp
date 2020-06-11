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

#include "Systems/Render.hpp"
#include "common/debug.hpp"

#include <Components/Sprite.hpp>
#include <Components/Transform.hpp>
#include <Components/Debug.hpp>
#include <Components/Velocity.hpp>

#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>
#include <algorithm>

static bool zComp (anax::Entity& e1, anax::Entity& e2) { 
    int z1 = e1.getComponent<SpriteComponent>().z;    
    int z2 = e2.getComponent<SpriteComponent>().z;    
    return (z1<z2);
}

void IRenderSystem::setRenderTarget(sf::RenderTarget& renderTarget){
    m_renderTarget = &renderTarget;
}

sf::RenderTarget& IRenderSystem::getRenderTarget() const {
    assert(isValid());
    return *m_renderTarget;
}

bool IRenderSystem::isValid() const {
    return m_renderTarget != nullptr;
}

void RenderSystem::render() {
    auto entities = getEntities();
    std::sort(entities.begin(), entities.end(), &zComp);
    for(auto& entity : entities) {
        auto& sprite = entity.getComponent<SpriteComponent>().sprite;
        auto& transform = entity.getComponent<TransformComponent>().transform;
        getRenderTarget().draw(sprite, transform.getTransform());
    }
}


void DebugRenderSystem::render(){
    auto entities = getEntities();
    for (auto& entity : entities){
        auto& map = entity.getComponent<DebugComponent>().map;
        for(auto& va : map){
            getRenderTarget().draw(va.second);
        }
    }
}