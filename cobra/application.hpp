#ifndef COBRA_APPLICATION_HPP
#define COBRA_APPLICATION_HPP

#include <memory>
#include <string>

#include "gmx/application.hpp"

namespace cobra {

enum {
    VERTICAL_PART, HORIZONTAL_PART,
    LEFT_PART, RIGHT_PART, TOP_PART, BOTTOM_PART,
    TOP_RIGHT_PART, TOP_LEFT_PART, BOTTOM_RIGHT_PART, BOTTOM_LEFT_PART,
    FOOD,


    // Enum com tamanho dinâmico. Contanto que a linha abaixo seja a última.
    REGION_SIZE
};

class Application : public gmx::StateApplication {
    public:
        Application() {}
        virtual ~Application() {}

    protected:
        virtual void create();
        virtual void update();
        virtual void dispose();

    private:
        // attributes
};

class BaseState : public gmx::DefaultState {
    public:
        BaseState(Application& app) : app(app) {}
        virtual ~BaseState() {}

        virtual void update();

    protected:
        virtual void handleInput() {}
        virtual void processLogic() {}
        virtual void draw() {}

        Application& app;
};

} /* namespace cobra */
#endif /* COBRA_APPLICATION_HPP */
