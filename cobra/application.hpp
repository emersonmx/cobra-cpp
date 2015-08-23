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
        Application() {}
        virtual ~Application() {}

        std::string getWindowTitle() { return windowTitle; }
        void setWindowTitle(const std::string& title) { windowTitle = title; }
        unsigned int getWindowWidth() { return windowWidth; }
        void setWindowWidth(unsigned int width) {windowWidth = width; }
        unsigned int getWindowHeight() { return windowHeight; }
        void setWindowHeight(unsigned int height) { windowHeight = height; }

        std::shared_ptr<sdl::Window>& getWindow() { return window; }
        std::shared_ptr<sdl::Renderer>& getRenderer() { return renderer; }
        SDL_Event& getEvent() { return event; }
        sdl::Timer& getTimer() { return timer; }

        std::shared_ptr<sdl::Texture>& getGame() { return game; }
        std::shared_ptr<sdl::TextureRegion>& getRegion() { return region; }

    protected:
        virtual void create();
        virtual void update();
        virtual void dispose();

    private:
        void initSDL();
        void createWindow();
        void createRenderer();
        void initSDLImage();
        void loadAssets();
        void setup();

        void unloadAssets();

        std::string windowTitle;
        unsigned int windowWidth;
        unsigned int windowHeight;

        std::shared_ptr<sdl::Window> window;
        std::shared_ptr<sdl::Renderer> renderer;
        SDL_Event event;

        sdl::Timer timer;

        std::shared_ptr<sdl::Texture> game;
        std::shared_ptr<sdl::TextureRegion> region;
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
