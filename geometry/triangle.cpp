#include "triangle.h"

Triangle::Triangle(int x1, int y1, int a, int b) {
    _x1 = x1;
    _y1 = y1;
    _a = a;
    _b = b;
    _pointsCount = 4;
}

SDL_Point* Triangle::geometry() {
    if (_geometry == NULL || _touch) {
        delete _geometry;
        _geometry = new SDL_Point[4];
        _geometry[0] = { _x1 + _a, _y1 };
        _geometry[1] = { _x1, _y1 };
        _geometry[2] = { _x1, _y1 + _b };
        _geometry[3] = _geometry[0];
        _touch = true;
    }

    return _geometry;
}

void Triangle::setStartPoints(int x, int y) {
    _x1 = x;
    _y1 = y;
    _a = 5;
    _b = 5;
    _touch = true;
}

void Triangle::setFinishPoints(int x, int y) {
    _a = x - _x1;
    _b = y - _y1;
    _touch = true;
}
