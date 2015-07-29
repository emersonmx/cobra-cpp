#ifndef COBRA_APPLICATION_HPP
#define COBRA_APPLICATION_HPP

#include <string>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"

#include "cobra/sdl.hpp"

namespace cobra {

class Cobra : public gmx::Application {
    public:
        Cobra();
        virtual ~Cobra();

        inline std::string getWindowTitle() { return windowTitle; }
        inline void setWindowTitle(const std::string& title) { windowTitle = title; }
        inline unsigned int getWindowWidth() { return windowWidth; }
        inline void setWindowWidth(unsigned int width) { windowWidth = width; }
        inline unsigned int getWindowHeight() { return windowHeight; }
        inline void setWindowHeight(unsigned int height) { windowHeight = height; }

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

        SDL_Window* window;
        sdl::Renderer* renderer;
        SDL_Event event;

        sdl::Timer timer;

        sdl::Texture* game;
        sdl::TextureRegion* region;
};

} /* namespace cobra */
#endif /* COBRA_APPLICATION_HPP */
