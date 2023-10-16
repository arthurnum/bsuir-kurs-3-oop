#ifndef H_LINE
#define H_LINE

#include "geometry.h"

class Line : public Geometry {
    public:
        Line(int x1, int y1, int x2, int y2);
        SDL_Point* geometry() override;
        void setStartPoints(int x, int y) override;
        void setFinishPoints(int x, int y) override;


    private:
        int _x1;
        int _x2;
        int _y1;
        int _y2;
};

#endif
