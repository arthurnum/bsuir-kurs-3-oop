#ifndef H_RECTANGLE
#define H_RECTANGLE

#include "geometry.h"

class Rectangle : public Geometry {
    public:
        Rectangle(int x1, int y1, int a, int b);
        SDL_Point* geometry() override;
        void setStartPoints(int x, int y) override;
        void setFinishPoints(int x, int y) override;


    private:
        int _x1;
        int _y1;
        int _a;
        int _b;
};

#endif
