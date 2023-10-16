#ifndef H_ELLIPSE
#define H_ELLIPSE

#include "geometry.h"

class Ellipse : public Geometry {
    public:
        Ellipse(int x1, int y1, int a, int b);
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
