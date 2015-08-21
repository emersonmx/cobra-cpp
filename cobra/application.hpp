#ifndef COBRA_APPLICATION_HPP
#define COBRA_APPLICATION_HPP

#include <memory>
#include <string>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"

#include "sdlutils/sdl.hpp"

namespace cobra {

class Application : public gmx::StateApplication {
    public:
        Application();
        virtual ~Application();

        std::string getWindowTitle();
        void setWindowTitle(const std::string& title);
        unsigned int getWindowWidth();
        void setWindowWidth(unsigned int width);
        unsigned int getWindowHeight();
        void setWindowHeight(unsigned int height);

    protected:
        virtual void create();
        virtual void dispose();
        virtual void update();

    private:
        void initSDL();
        void createWindow();
        void createRenderer();
        void initSDLImage();
        void loadAssets();
        void setup();

        void unloadAssets();

        void handleInput();
        void processLogic();
        void draw();

        std::string windowTitle;
        unsigned int windowWidth;
        unsigned int windowHeight;

        sdl::Window* window;
        sdl::Renderer* renderer;
        SDL_Event event;

        sdl::Timer timer;

        sdl::Texture* game;
        sdl::TextureRegion* region;
};

} /* namespace cobra */
#endif /* COBRA_APPLICATION_HPP */
