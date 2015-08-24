#include "cobra/application.hpp"
#include "cobra/game.hpp"

#include <iostream>
#include <memory>

using namespace std;

namespace cobra {

void Application::create() {
    try {
        initSDL();
        createWindow();
        createRenderer();
        initSDLImage();
        loadAssets();
        setup();
    } catch (exception& e) {
        cout << e.what() << endl; exit(-1);
    } catch (...) {
        cout << "Ocorreu um erro desconhecido." << endl;
        exit(-1);
    }
}

void Application::initSDL() {
    Uint32 flags = SDL_INIT_VIDEO;
    if (SDL_Init(flags) != 0) {
        throw sdl::Error();
    }
}

void Application::createWindow() {
    window = make_shared<sdl::Window>(windowTitle, windowWidth, windowHeight);
    window->show();
}

void Application::createRenderer() {
    renderer = make_shared<sdl::Renderer>(*window);
}

void Application::initSDLImage() {
    Uint32 flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        throw sdl::Error();
    }
}

void Application::loadAssets() {
    game = sdl::loadTexture(*renderer, "assets/game.png");

    regions[VERTICAL_PART] = make_shared<sdl::TextureRegion>(*game, 0, 0, 8, 8);
    regions[TOP_RIGHT_PART] = make_shared<sdl::TextureRegion>(*game, 8, 0, 8, 8);
    regions[TOP_LEFT_PART] = make_shared<sdl::TextureRegion>(*game, 16, 0, 8, 8);
    regions[TOP_PART] = make_shared<sdl::TextureRegion>(*game, 24, 0, 8, 8);

    regions[RIGHT_PART] = make_shared<sdl::TextureRegion>(*game, 0, 8, 8, 8);
    regions[LEFT_PART] = make_shared<sdl::TextureRegion>(*game, 8, 8, 8, 8);
    regions[HORIZONTAL_PART] = make_shared<sdl::TextureRegion>(*game, 16, 8, 8, 8);
    regions[FOOD] = make_shared<sdl::TextureRegion>(*game, 24, 8, 8, 8);

    regions[BOTTOM_RIGHT_PART] = make_shared<sdl::TextureRegion>(*game, 0, 16, 8, 8);
    regions[BOTTOM_LEFT_PART] = make_shared<sdl::TextureRegion>(*game, 8, 16, 8, 8);
    regions[BOTTOM_PART] = make_shared<sdl::TextureRegion>(*game, 16, 16, 8, 8);
}

void Application::setup() {
    timer.setup();
}

void Application::update() {
    timer.update();
    StateApplication::update();
}

void Application::dispose() {
    unloadAssets();

    renderer.reset();
    window.reset();

    IMG_Quit();
    SDL_Quit();
}

void Application::unloadAssets() {
    game.reset();
}

void BaseState::update() {
    handleInput();
    processLogic();
    draw();
}

} /* namespace cobra */

int main() {
    cobra::Application app;
    app.setWindowTitle("Cobra");
    app.setWindowWidth(500);
    app.setWindowHeight(500);

    shared_ptr<cobra::GameState> gameState = make_shared<cobra::GameState>(app);
    app.setState(gameState);

    return app.run();
}
