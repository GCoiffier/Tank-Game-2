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

#pragma once

#include <vector>

#include <anax/System.hpp>

#include <Components/Transform.hpp>
#include <Components/Collision.hpp>

/// \brief A system that handles collisions
///
/// This system handles collisions. It uses entities with the following components:
///		- Transform
///		- Collision
///
/// \author Miguel Martin
struct CollisionSystem : anax::System<anax::Requires<TransformComponent, CollisionComponent>> {
public:

    /// Updates the collision system
    /// \param deltaTime The change in time
    void update(double deltaTime);

private:
    void onCollisionOccured(anax::Entity& e1, anax::Entity& e2, double deltaTime=0.);

    void handleCollisionBullet(anax::Entity& bullet, anax::Entity& collided, double deltaTime=0.);
    void handleCollisionPlayer(anax::Entity& player, anax::Entity& collided, double deltaTime=0.);

};