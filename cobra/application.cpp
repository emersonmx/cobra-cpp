#include "cobra/application.hpp"

#include <iostream>
#include <memory>

using namespace std;

namespace cobra {

Application::Application() : window(NULL) {}

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

void Application::create() {
    try {
        initSDL();
        createWindow();
        createRenderer();
        initSDLImage();
        loadAssets();
        setup();
    } catch (exception& e) {
        cout << e.what() << endl;
        exit(-1);
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
    window = new sdl::Window(windowTitle, windowWidth, windowHeight);
    window->show();
}

void Application::createRenderer() {
    renderer = new sdl::Renderer();
    renderer->create(window);
}

void Application::initSDLImage() {
    Uint32 flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        throw sdl::Error();
    }
}

void Application::loadAssets() {
    game = sdl::loadTexture(renderer->getSDLRenderer(), "assets/game.png");
    region = new sdl::TextureRegion(game);
    region->setRegion(0, 0, 8, 8);
}

void Application::setup() {
    timer.setup();
}

void Application::dispose() {
    unloadAssets();

    delete renderer;
    delete window;

    IMG_Quit();
    SDL_Quit();
}

void Application::unloadAssets() {
    delete region;
    delete game;
}

void Application::update() {
    handleInput();
    processLogic();
    draw();
}

void Application::handleInput() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
    }
}

void Application::processLogic() {
    timer.update();
}

void Application::draw() {
    renderer->clear();
    renderer->draw(region, 0, 0);
    renderer->draw(game, 100, 100);
    renderer->present();
}

} /* namespace cobra */

int main() {
    cobra::Application app;
    app.setWindowTitle("Cobra");
    app.setWindowWidth(500);
    app.setWindowHeight(500);

    return app.run();
}
