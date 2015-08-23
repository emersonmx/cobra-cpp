#ifndef COBRA_GAME_HPP
#define COBRA_GAME_HPP

#include "cobra/application.hpp"

namespace cobra {

class GameState : public BaseState {
    public:
        GameState(Application& app) : BaseState(app) {}
        virtual ~GameState() {}

    protected:
        virtual void handleInput();
        virtual void processLogic();
        virtual void draw();
};

} /* namespace cobra */
#endif /* COBRA_GAME_HPP */
