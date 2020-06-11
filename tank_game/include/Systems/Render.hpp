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

#include <anax/System.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Components.hpp"

struct IRenderSystem {
    virtual void render() = 0;

    IRenderSystem(sf::RenderTarget& renderTarget)  : m_renderTarget(&renderTarget) {}

    void setRenderTarget(sf::RenderTarget& renderTarget);
    sf::RenderTarget& getRenderTarget() const;
    bool isValid() const;

private:
    sf::RenderTarget* m_renderTarget;
};

struct RenderSystem :
    public IRenderSystem,
    public anax::System<
        anax::Requires<SpriteComponent, TransformComponent>>
{
    RenderSystem(sf::RenderTarget& renderTarget) : IRenderSystem(renderTarget) {}
    void render();
};


struct DebugRenderSystem :
    public IRenderSystem,
    public anax::System<
        anax::Requires<DebugComponent>>
{
    DebugRenderSystem(sf::RenderTarget& renderTarget) : IRenderSystem(renderTarget) {}
    void render();
};