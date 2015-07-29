#ifndef SDL_UTILS_HPP
#define SDL_UTILS_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>

#include "gmx/graphics.hpp"

namespace sdl {

class Texture : public gmx::Texture<SDL_Texture*> {
    public:
        Texture(SDL_Texture* texture, int width, int height)
            : gmx::Texture<SDL_Texture*>(texture, width, height) {}
        virtual ~Texture() {
            SDL_DestroyTexture(texture);
        }
};

class TextureRegion : public gmx::TextureRegion<SDL_Texture*> {
    public:
        TextureRegion(Texture* texture)
            : gmx::TextureRegion<SDL_Texture*>(texture) {}
        virtual ~TextureRegion() {}
};

class Timer {
    public:
        Timer() : delta(0.f), lastTicks(0) {}
        inline float getDelta() { return delta; }

        void setup() {
            lastTicks = SDL_GetTicks();
        }

        float update() {
            Uint32 ticks = SDL_GetTicks();
            delta = (ticks - lastTicks) / 1000.f;
            lastTicks = ticks;
            return delta;
        }

    private:
        float delta;
        Uint32 lastTicks;
};

class Renderer {
    public:
        Renderer() : renderer(NULL) {}
        virtual ~Renderer() {
            SDL_DestroyRenderer(renderer);
        }

        inline SDL_Renderer* getRenderer() { return renderer; }

        void create(SDL_Window* window, Uint32 flags=SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) {
            renderer = SDL_CreateRenderer(window, -1, flags);
            if (renderer == NULL) {
                throw std::logic_error("Não foi possível criar o renderer.");
            }
            setDrawColor(0, 0, 0, 0);
        }

        Texture* loadTexture(std::string filename) {
            SDL_Texture* sdltexture = IMG_LoadTexture(renderer, filename.c_str());
            if (sdltexture == NULL) {
                return NULL;
            }

            int w, h;
            SDL_QueryTexture(sdltexture, NULL, NULL, &w, &h);

            return new Texture(sdltexture, w, h);
        }

        void setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
            SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
        }

        void draw(Texture* texture, int x, int y) {
            SDL_Rect offset;
            offset.x = x;
            offset.y = y;
            offset.w = texture->getWidth();
            offset.h = texture->getHeight();
            draw(texture->getTexture(), NULL, &offset);
        }

        void draw(TextureRegion* region, int x, int y) {
            SDL_Rect offset;
            SDL_Rect offsetSource;

            offset.x = x;
            offset.y = y;
            offset.w = region->getWidth();
            offset.h = region->getHeight();

            offsetSource.x = region->getX();
            offsetSource.y = region->getY();
            offsetSource.w = region->getWidth();
            offsetSource.h = region->getHeight();

            draw(region->getRawTexture(), &offsetSource, &offset);
        }

        inline void draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* offset) {
            SDL_RenderCopy(renderer, texture, source, offset);
        }

        inline void clear() {
            SDL_RenderClear(renderer);
        }

        inline void present() {
            SDL_RenderPresent(renderer);
        }

    private:
        SDL_Renderer* renderer;
};


} /* namespace sdl */
#endif /* SDL_UTILS_HPP */
