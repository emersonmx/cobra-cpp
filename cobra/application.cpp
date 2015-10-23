#include "application.hpp"

namespace cobra {

void Application::exit() {
    exit(0);
}

void Application::exit(int errorCode) {
    running = false;
    errorCode = errorCode;
}

int Application::run() {
    create();

    while (running) {
        render();
    }

    dispose();

    return errorCode;
}

void Application::render() {
    processInput();
    update();
    draw();
}

void Application::create() {
    window.create(sf::VideoMode(500, 500), "Cobra"); 
    window.setVerticalSyncEnabled(true);
}

void Application::dispose() {
    window.close();
}

void Application::processInput() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            exit();
        }
    }
}

void Application::update() {
}

void Application::draw() {
    window.clear(sf::Color::Black);
    window.display();
}

} /* namespace cobra */ 
