#include "parallelogram.h"

Parallelogram::Parallelogram(int x1, int y1, int a, int b, int angleDegree) {
    _x1 = x1;
    _y1 = y1;
    _a = a;
    _b = b;
    _angleDegree = angleDegree;
    _angleRadian = PI * angleDegree / 180.0;
    _pointsCount = 5;
}

SDL_Point* Parallelogram::geometry() {
    if (_geometry == NULL || _touch) {
        _geometry = new SDL_Point[5];
        _geometry[0] = { _x1, _y1 };
        _geometry[1] = { _x1 + _a, _y1 };
        _geometry[2] = {
            _geometry[1].x + int(_b * sin(_angleRadian)),
            _geometry[1].y + int(_b * cos(_angleRadian))
        };
        _geometry[3] = {
            _geometry[2].x - _a,
            _geometry[2].y
        };
        _geometry[4] = { _x1, _y1 };
        _touch = false;
    }

    return _geometry;
}

void Parallelogram::setStartPoints(int x, int y) {
    _x1 = x;
    _y1 = y;
    _a = 5;
    _b = 5;
    _angleDegree = 0;
    _angleRadian = PI * _angleDegree / 180.0;
    _touch = true;
}

void Parallelogram::setFinishPoints(int x, int y) {
    _a = x - _x1;
    _b = y - _y1;
    _angleRadian = atan2(_a, _b);
    _touch = true;
}
