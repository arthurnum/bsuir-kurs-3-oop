#ifndef H_GEOMETRY
#define H_GEOMETRY

#include <SDL.h>
#include <cmath>

const double PI = 3.1415926535;

class Geometry {
    public:
        virtual SDL_Point* geometry() = 0;
        virtual void setStartPoints(int x, int y) = 0;
        virtual void setFinishPoints(int x, int y) = 0;
        virtual void move(int dx, int dy) = 0;
        int getPointsCount() { return _pointsCount; };
        void take() { _active = true; }
        void drop() { _active = false; }
        bool active() { return _active; }
        int* color() {
            // return (_active) ? _activeColor : _color;
            return _color;
        }
        void setColor(int r, int g, int b) {
            _color[0] = r;
            _color[1] = g;
            _color[2] = b;
        }

    protected:
        SDL_Point* _geometry;
        int _pointsCount;
        bool _touch;
        bool _active;
        int _color[3] = { 255, 255, 255 };
        int _activeColor[3] = { 115, 225, 115 };
};

#endif
