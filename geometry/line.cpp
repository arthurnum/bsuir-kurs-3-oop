#include "line.h"

Line::Line(int x1, int y1, int x2, int y2) {
    _gtype = GEOMETRY_LINE;
    _x1 = x1;
    _x2 = x2;
    _y1 = y1;
    _y2 = y2;
    _pointsCount = 2;
}

Line::Line(int psize, SDL_Point* points) {
    _gtype = GEOMETRY_LINE;
    _pointsCount = psize;
    _geometry = new SDL_Point[psize];
    std::memcpy(_geometry, points, sizeof(SDL_Point)*psize);
}

SDL_Point* Line::geometry() {
    if (_geometry == NULL || _touch) {
        delete _geometry;
        _geometry = new SDL_Point[2];
        _geometry[0] = { _x1, _y1 };
        _geometry[1] = { _x2, _y2 };
        _touch = false;
    }

    return _geometry;
}

void Line::setStartPoints(int x, int y) {
    _x1 = x;
    _y1 = y;
    _x2 = x;
    _y2 = y;
    _touch = true;
}

void Line::setFinishPoints(int x, int y) {
    _x2 = x;
    _y2 = y;
    _touch = true;
}

void Line::move(int dx, int dy) {
    _x1 += dx;
    _y1 += dy;
    _x2 += dx;
    _y2 += dy;
    _touch = true;
}
