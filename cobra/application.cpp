#include "cobra/application.hpp"

#include <iostream>
#include <memory>

using namespace std;

namespace cobra {

Cobra::Cobra() : window(NULL) {}

Cobra::~Cobra() {
}

string Cobra::getWindowTitle() {
    return windowTitle;
}

void Cobra::setWindowTitle(const string& title) {
    windowTitle = title;
}

unsigned int Cobra::getWindowWidth() {
    return windowWidth;
}

void Cobra::setWindowWidth(unsigned int width) {
    windowWidth = width;
}

unsigned int Cobra::getWindowHeight() {
    return windowHeight;
}

void Cobra::setWindowHeight(unsigned int height) {
    windowHeight = height;
}

void Cobra::create() {
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

void Cobra::initSDL() {
    Uint32 flags = SDL_INIT_VIDEO;
    if (SDL_Init(flags) != 0) {
        throw sdl::Error();
    }
}

void Cobra::createWindow() {
    window = new sdl::Window(windowTitle, windowWidth, windowHeight);
    window->show();
}

void Cobra::createRenderer() {
    renderer = new sdl::Renderer();
    renderer->create(window);
}

void Cobra::initSDLImage() {
    Uint32 flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        throw sdl::Error();
    }
}

void Cobra::loadAssets() {
    game = sdl::loadTexture(renderer->getSDLRenderer(), "assets/game.png");
    region = new sdl::TextureRegion(game);
    region->setRegion(0, 0, 8, 8);
}

void Cobra::setup() {
    timer.setup();
}

void Cobra::dispose() {
    unloadAssets();

    delete renderer;
    delete window;

    IMG_Quit();
    SDL_Quit();
}

void Cobra::unloadAssets() {
    delete region;
    delete game;
}

void Cobra::update() {
    handleInput();
    processLogic();
    draw();
}

void Cobra::handleInput() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
    }
}

void Cobra::processLogic() {
    timer.update();
}

void Cobra::draw() {
    renderer->clear();
    renderer->draw(region, 0, 0);
    renderer->draw(game, 100, 100);
    renderer->present();
}

} /* namespace cobra */

int main() {
    cobra::Cobra cobra;
    cobra.setWindowTitle("Cobra");
    cobra.setWindowWidth(500);
    cobra.setWindowHeight(500);

    return cobra.run();
}
