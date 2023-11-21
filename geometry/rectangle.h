#ifndef H_RECTANGLE
#define H_RECTANGLE

#include "geometry.h"

class Rectangle : public Geometry {
    public:
        Rectangle(int x1, int y1, int a, int b);
        Rectangle(int psize, SDL_Point* points);
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
