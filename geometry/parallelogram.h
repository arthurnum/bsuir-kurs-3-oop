#ifndef H_PARALLELOGRAM
#define H_PARALLELOGRAM

#include "geometry.h"

class Parallelogram : public Geometry {
    public:
        Parallelogram(int x1, int y1, int a, int b, int angleDegree);
        SDL_Point* geometry() override;
        void setStartPoints(int x, int y) override;
        void setFinishPoints(int x, int y) override;

    private:
        int _x1;
        int _y1;
        int _a;
        int _b;
        int _angleDegree;
        double _angleRadian;
};

#endif
