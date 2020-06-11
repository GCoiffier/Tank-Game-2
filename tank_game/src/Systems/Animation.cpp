#include "Systems/Animation.hpp"

#include <iostream>

void AnimationSystem::update(double deltaTime) {
    auto entities = getEntities();
    for(auto& e : entities) {		
        auto& animation = e.getComponent<AnimationComponent>();
        
        if (animation.frames_since_last_update < animation.fps) {
            animation.frames_since_last_update++;
        } else {
            animation.frames_since_last_update = 0;
            animation.currentFrame = (animation.currentFrame + 1) % animation.nFrames;
                
            auto& sprite = e.getComponent<SpriteComponent>().sprite;
            sf::IntRect rect(sf::Vector2i(animation.currentFrame * animation.frameSize.x, 0), sf::Vector2i(animation.frameSize)); 
            sprite.setTextureRect(rect);
        }
    }
}
