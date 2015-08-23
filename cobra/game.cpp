#include "cobra/game.hpp"

#include <iostream>

using namespace std;

namespace cobra {

void GameState::handleInput() {
    auto& event = app.getEvent();
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
    }
}

void GameState::processLogic() {
}

void GameState::draw() {
    auto& renderer = app.getRenderer();
    auto& game = app.getGame();
    auto& region = app.getRegion();

    renderer->clear();
    renderer->draw(&region, 0, 0);
    renderer->draw(game.get(), 100, 100);
    renderer->present();
}

} /* namespace cobra */
