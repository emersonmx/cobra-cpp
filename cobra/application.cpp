#include "cobra/application.hpp"
#include "cobra/game.hpp"

#include <iostream>
#include <memory>

using namespace std;

namespace cobra {

Application::Application() {}

Application::~Application() {
}

string Application::getWindowTitle() {
    return windowTitle;
}

void Application::setWindowTitle(const string& title) {
    windowTitle = title;
}

unsigned int Application::getWindowWidth() {
    return windowWidth;
}

void Application::setWindowWidth(unsigned int width) {
    windowWidth = width;
}

unsigned int Application::getWindowHeight() {
    return windowHeight;
}

void Application::setWindowHeight(unsigned int height) {
    windowHeight = height;
}

WindowPtr& Application::getWindow() {
    return window;
}

RendererPtr& Application::getRenderer() {
    return renderer;
}

SDL_Event& Application::getEvent() {
    return event;
}

sdl::Timer& Application::getTimer() {
    return timer;
}

TexturePtr& Application::getGame() {
    return game;
}

TextureRegionPtr& Application::getRegion() {
    return region;
}

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
    window.reset(new sdl::Window(windowTitle, windowWidth, windowHeight));
    window->show();
}

void Application::createRenderer() {
    renderer.reset(new sdl::Renderer());
    renderer->create(window.get());
}

void Application::initSDLImage() {
    Uint32 flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        throw sdl::Error();
    }
}

void Application::loadAssets() {
    game.reset(sdl::loadTexture(renderer->getSDLRenderer(), "assets/game.png"));
    region.reset(new sdl::TextureRegion(game.get()));
    region->setRegion(0, 0, 8, 8);
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
    region.reset();
    game.reset();
}

BaseState::BaseState(Application& app) : app(app) {}

BaseState::~BaseState() {}

WindowPtr& BaseState::getWindow() {
    return app.getWindow();
}

RendererPtr& BaseState::getRenderer() {
    return app.getRenderer();
}

SDL_Event& BaseState::getEvent() {
    return app.getEvent();
}

sdl::Timer& BaseState::getTimer() {
    return app.getTimer();
}

TexturePtr& BaseState::getGame() {
    return app.getGame();
}

TextureRegionPtr& BaseState::getRegion() {
    return app.getRegion();
}

void BaseState::update() {
    handleInput();
    processLogic();
    draw();
}

void BaseState::handleInput() {}

void BaseState::processLogic() {}

void BaseState::draw() {}

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
