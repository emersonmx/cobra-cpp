#ifndef COBRA_COBRA_HPP
#define COBRA_COBRA_HPP

#include <deque>

namespace cobra {

class Cobra {
    typedef enum {
        UP, RIGHT, DOWN, LEFT, DIRECTION_SIZE
    } Direction;

    public:
        typedef struct {
            int x;
            int y;
            int direction;
        } Part;

        Cobra();
        virtual ~Cobra() {}

        Part getHead() { return body.front(); }
        Part getTail() { return body.back(); }
        int getDirection() { return direction; }
        void setDirection(int direction);
        std::deque<Part>& getBody() { return body; }
        void setBody(std::deque<Part>& body) { this->body = body; }

        void eat();
        void update();

    protected:
        bool canTurn(int direction);
        Part move();

        std::deque<Part> body;
        int direction;
        int inputDirection;
};

class World {
    public:
        Cobra& getCobra() { return cobra; }
        void setCobra(const Cobra& cobra) { this->cobra = cobra; }

        int getWidth() { return width; }
        void setWidth(int width) { this->width = width; }
        int getHeight() { return height; }
        void setHeight(int height) { this->height = height; }
        void getSize(int* width, int* height) {
            *width = this->width;
            *height = this->height;
        }
        void setSize(int width, int height) {
            this->width = width;
            this->height = height;
        }

    protected:
        Cobra cobra;

        int width;
        int height;
};

} /* namespace cobra */
#endif /* COBRA_COBRA_HPP */
