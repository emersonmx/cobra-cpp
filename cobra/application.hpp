#ifndef COBRA_APPLICATION_HPP
#define COBRA_APPLICATION_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace cobra {

class Application {
    public:
        int getErrorCode() { return errorCode; }

        void exit();
        void exit(int errorCode);
        int run();

    protected:
        void create();
        void dispose();

        void render();
        void processInput();
        void update();
        void draw();

        sf::RenderWindow window;
        sf::Event event;

    private:
        int errorCode = 0;
        bool running = true;
};

} /* namespace cobra */ 
#endif /* COBRA_APPLICATION_HPP */
