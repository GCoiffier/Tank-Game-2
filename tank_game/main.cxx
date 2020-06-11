#include "Level.hpp"
#include "InputManager.hpp"
#include "common/debug.hpp"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>
#include <string>

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 800;

/// A typedef that is used to represent a second
typedef double Seconds;

/// \return The systems time now
inline Seconds GetTimeNow() {
    using namespace std;
    return chrono::duration_cast<chrono::duration<Seconds>>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Tank Game 2");

    Level level(window);
    level.load_from_file("level_test");

    const float MAX_FRAME_TIME = 1 / 4.f;
    const float DELTA_TIME = 1 / 60.f;
    Seconds currentTime = 0; // Holds the current time
    Seconds accumulator = 0; // Used to accumlate time in the game loop

    sf::Event event;
    while(level.isRunning()) {
        
        while(window.pollEvent(event)) {
            level.handleEvents(event);
        }

        USER_INPUTS.read_inputs(window);

        Seconds newTime = GetTimeNow();
        Seconds frameTime = newTime - currentTime;
        currentTime = newTime;

        // cap the loop delta time
        if(frameTime >= MAX_FRAME_TIME) {
            frameTime = MAX_FRAME_TIME;
        }

        accumulator += frameTime;

        // Update our game
        while(accumulator >= DELTA_TIME) {
            level.update(DELTA_TIME); // update the game (with the constant delta time)
            accumulator -= DELTA_TIME; // decrease the accumulator
        }

        level.render();
        window.display();
    }

    return 0;
}
