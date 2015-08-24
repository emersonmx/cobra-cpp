#include "cobra/cobra.hpp"

using namespace std;

namespace cobra {

Cobra::Cobra() {
    direction = inputDirection = RIGHT;
}

void Cobra::setDirection(int direction) {
    if (canTurn(direction)) {
        inputDirection = direction;
    }
}

void Cobra::eat() {
    body.push_back(getTail());
}

void Cobra::update() {
    direction = inputDirection;
    auto newHead = move();
    body.push_front(newHead);
    body.pop_back();
}

bool Cobra::canTurn(int direction) {
    return ((direction + this->direction) % 2) == 1;
}

Cobra::Part Cobra::move() {
    auto head = getHead();
    int x = head.x;
    int y = head.y;
    if (direction == UP) {
        y++;
    } else if (direction == DOWN) {
        y--;
    } else if (direction == LEFT) {
        x--;
    } else if (direction == RIGHT) {
        x++;
    }

    Part newHead = { x, y, direction };
    return newHead;
}

} /* namespace cobra */
