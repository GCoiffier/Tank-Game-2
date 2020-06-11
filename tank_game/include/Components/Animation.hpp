#pragma once

#include <SFML/System/Vector2.hpp>
#include <anax/Component.hpp>
#include <json.hpp>

struct AnimationComponent : anax::Component {

    AnimationComponent(): AnimationComponent({0, 0}, 10, 1) {}
        
    AnimationComponent(sf::Vector2u _frameSize, unsigned int _fps, unsigned int _nFrames)
    :
        frameSize(_frameSize),
        fps(_fps),
        nFrames(_nFrames)
    {}

    AnimationComponent(const nlohmann::json& j){
        frameSize.x = j["frameSize"][0].get<unsigned int>();
        frameSize.y = j["frameSize"][1].get<unsigned int>();
        fps = j["fps"].get<unsigned int>();
        nFrames = j["nframes"].get<unsigned int>();
    }

    /** The size of each frame **/
    sf::Vector2u frameSize;

    /** number of frames between each updates **/
    unsigned int fps;
    unsigned int frames_since_last_update;
    unsigned int nFrames;
    unsigned int currentFrame;
};
