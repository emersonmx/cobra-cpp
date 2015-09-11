#include "cobra/application.hpp"
#include "cobra/game.hpp"

#include <memory>

using namespace std;

int main() {
    cobra::Application app;

    shared_ptr<cobra::GameState> gameState = make_shared<cobra::GameState>(app);
    app.setState(gameState);

    return app.run();
}
