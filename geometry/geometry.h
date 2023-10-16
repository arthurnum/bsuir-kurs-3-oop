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
        int getPointsCount() { return _pointsCount; };

    protected:
        SDL_Point* _geometry;
        int _pointsCount;
        bool _touch;
};

#endif
