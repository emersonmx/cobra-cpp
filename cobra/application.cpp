#include "cobra/application.hpp"
#include "cobra/game.hpp"

#include <iostream>
#include <memory>

using namespace std;

namespace cobra {

void Application::create() {
    try {
    } catch (exception& e) {
        cout << e.what() << endl; exit(-1);
    } catch (...) {
        cout << "Ocorreu um erro desconhecido." << endl;
        exit(-1);
    }
}

void Application::update() {
    StateApplication::update();
}

void Application::dispose() {
}

void BaseState::update() {
    handleInput();
    processLogic();
    draw();
}

} /* namespace cobra */

int main() {
    cobra::Application app;

    shared_ptr<cobra::GameState> gameState = make_shared<cobra::GameState>(app);
    app.setState(gameState);

    return app.run();
}
