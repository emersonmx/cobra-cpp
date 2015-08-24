#include "cobra/game.hpp"

#include <iostream>

using namespace std;

namespace cobra {

void GameState::enter() {
    index = 0;
}

void GameState::exit() {
}

void GameState::handleInput() {
    auto& event = app.getEvent();
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.exit(0);
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym = SDLK_SPACE) {
                index = (index + 1) % REGION_SIZE;
            }
        }
    }
}

void GameState::processLogic() {
}

void GameState::draw() {
    auto& renderer = app.getRenderer();
    auto& region = app.getRegion(index);

    renderer->clear();
    renderer->draw(*region, 100, 100);
    renderer->present();
}

} /* namespace cobra */
