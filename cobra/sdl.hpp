#ifndef SDL_UTILS_HPP
#define SDL_UTILS_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <stdexcept>

#include "gmx/graphics.hpp"

namespace sdl {

class Error : public std::logic_error {
    public:
        Error();
        Error(const std::string message);
};

class Texture : public gmx::Texture<SDL_Texture*> {
    public:
        Texture(SDL_Texture* texture, int width, int height);
        virtual ~Texture();
};

class TextureRegion : public gmx::TextureRegion<SDL_Texture*> {
    public:
        TextureRegion(Texture* texture);
        virtual ~TextureRegion();

        SDL_Texture* getSDLTexture();
};

class Timer {
    public:
        Timer();

        float getDelta();

        void setup();
        float update();

    private:
        float delta;
        Uint32 lastTicks;
};

class Window {
    public:
        Window(const std::string& title, int width, int height,
               Uint32 flags=SDL_WINDOW_HIDDEN);
        Window(const std::string& title, int x, int y, int width, int height,
               Uint32 flags=SDL_WINDOW_HIDDEN);
        virtual ~Window();

        SDL_Window* getSDLWindow();

        std::string getTitle();
        void setTitle(const std::string& title);
        void getSize(int* width, int* height);
        void setSize(int width, int height);
        SDL_Surface* getSurface();

        void show();
        void hide();
        void restore();
        void maximize();
        void minimize();
        int refresh();

    protected:
        SDL_Window* window;
};

class Renderer {
    public:
        static const Uint32 DEFAULT_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        Renderer();
        virtual ~Renderer();

        SDL_Renderer* getSDLRenderer();

        void create(Window* window, Uint32 flags=DEFAULT_FLAGS);
        void create(SDL_Window* window, Uint32 flags=DEFAULT_FLAGS);
        void setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
        void draw(Texture* texture, int x, int y);
        void draw(TextureRegion* region, int x, int y);
        void draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* offset);
        void clear();
        void present();

    private:
        SDL_Renderer* renderer;
};

Texture* loadTexture(SDL_Renderer* renderer, std::string filename);

} /* namespace sdl */
#endif /* SDL_UTILS_HPP */
