#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "geometry.h"

class Triangle : public Geometry {
    public:
        Triangle(int x1, int y1, int a, int b);
        Triangle(int psize, SDL_Point* points);
        SDL_Point* geometry() override;
        void setStartPoints(int x, int y) override;
        void setFinishPoints(int x, int y) override;
        void move(int dx, int dy) override;


    private:
        int _x1;
        int _y1;
        int _a;
        int _b;
};

#endif
