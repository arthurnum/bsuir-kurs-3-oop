#include "rectangle.h"

Rectangle::Rectangle(int x1, int y1, int a, int b) {
    _gtype = GEOMETRY_RECTANGLE;
    _x1 = x1;
    _y1 = y1;
    _a = a;
    _b = b;
    _pointsCount = 5;
}

Rectangle::Rectangle(int psize, SDL_Point* points) {
    _gtype = GEOMETRY_RECTANGLE;
    _pointsCount = psize;
    _geometry = new SDL_Point[psize];
    std::memcpy(_geometry, points, sizeof(SDL_Point)*psize);
}

SDL_Point* Rectangle::geometry() {
    if (_geometry == NULL || _touch) {
        delete _geometry;
        _geometry = new SDL_Point[5];
        _geometry[0] = { _x1, _y1 };
        _geometry[1] = { _x1 + _a, _y1 };
        _geometry[2] = { _x1 + _a, _y1 + _b };
        _geometry[3] = { _x1, _y1 + _b };
        _geometry[4] = { _x1, _y1 };
        _touch = false;
    }

    return _geometry;
}

void Rectangle::setStartPoints(int x, int y) {
    _x1 = x;
    _y1 = y;
    _a = 5;
    _b = 5;
    _touch = true;
}

void Rectangle::setFinishPoints(int x, int y) {
    _a = x - _x1;
    _b = y - _y1;
    _touch = true;
}

void Rectangle::move(int dx, int dy) {
    _x1 += dx;
    _y1 += dy;
    _touch = true;
}
