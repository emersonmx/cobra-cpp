#include "cobra/game.hpp"

#include <iostream>

using namespace std;

namespace cobra {

GameState::GameState(Application& app) : BaseState(app) {}

GameState::~GameState() {}

void GameState::handleInput() {
    SDL_Event& event = getEvent();
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
    }
}

void GameState::processLogic() {
}

void GameState::draw() {
    RendererPtr& renderer = getRenderer();
    TexturePtr& game = getGame();
    sdl::TextureRegion& region = getRegion();

    renderer->clear();
    renderer->draw(&region, 0, 0);
    renderer->draw(game.get(), 100, 100);
    renderer->present();
}

} /* namespace cobra */
