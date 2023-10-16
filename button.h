#ifndef H_BUTTON
#define H_BUTTON

#include <functional>

#include "geometry/geometry.h"
#include "geometry/geometry_set.h"

typedef std::function<void(int)> OnClickFn;

class Button {
    public:
        Button(int x1, int y1, int x2, int y2, GeometrySet* geometry_set) {
            _geometry_set = geometry_set;
            for (Geometry* item : *_geometry_set->items()) {
                item->setColor(200, 200, 255);
            }
            _x1 = x1;
            _x2 = x2;
            _y1 = y1;
            _y2 = y2;
        };
        GeometrySet* geometrySet() { return _geometry_set; };
        void handleMouseButton(SDL_MouseButtonEvent event);
        OnClickFn onClick;

    private:
        GeometrySet* _geometry_set;
        int _x1;
        int _x2;
        int _y1;
        int _y2;
};

#endif
