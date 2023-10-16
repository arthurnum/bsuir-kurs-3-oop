#include "ellipse.h"

Ellipse::Ellipse(int x1, int y1, int a, int b) {
    _x1 = x1;
    _y1 = y1;
    _a = a;
    _b = b;
    _pointsCount = 32;
}

SDL_Point* Ellipse::geometry() {
    if (_geometry == NULL || _touch) {
        delete _geometry;
        _geometry = new SDL_Point[32];
        for (int i = 0; i < 31; i++) {
            _geometry[i] = {
                _x1 + int(_a * sin(2 * PI * i / 31)),
                _y1 + int(_b * cos(2 * PI * i / 31))
            };
        }
        _geometry[31] = _geometry[0];
        _touch = false;
    }

    return _geometry;
}

void Ellipse::setStartPoints(int x, int y) {
    _x1 = x;
    _y1 = y;
    _a = 5;
    _b = 5;
    _touch = true;
}

void Ellipse::setFinishPoints(int x, int y) {
    _a = abs(x - _x1);
    _b = abs(y - _y1);
    _touch = true;
}

void Ellipse::move(int dx, int dy) {
    _x1 += dx;
    _y1 += dy;
    _touch = true;
}
