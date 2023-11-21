#ifndef H_GEOMETRY
#define H_GEOMETRY

#include <SDL.h>
#include <cmath>
#include <cstring>


const unsigned char GEOMETRY_ELLIPSE = 101;
const unsigned char GEOMETRY_LINE = 102;
const unsigned char GEOMETRY_PARALLELOGRAM = 103;
const unsigned char GEOMETRY_RECTANGLE = 104;
const unsigned char GEOMETRY_TRIANGLE = 105;

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
            return _color;
        }
        void setColor(int r, int g, int b) {
            _color[0] = r;
            _color[1] = g;
            _color[2] = b;
        }
        unsigned char geometryType() { return _gtype; }

    protected:
        unsigned char _gtype;
        SDL_Point* _geometry;
        int _pointsCount;
        bool _touch;
        bool _active;
        int _color[3] = { 255, 255, 255 };
};

#endif
