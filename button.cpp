#include "button.h"

void Button::handleMouseButton(SDL_MouseButtonEvent event) {
    if (event.x < _x1) { return; }
    if (event.x > _x2) { return; }
    if (event.y < _y1) { return; }
    if (event.y > _y2) { return; }

    if (onClick) { onClick(5); }
}
