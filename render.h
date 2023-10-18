#ifndef H_RENDER
#define H_RENDER

#include <SDL.h>

#include "geometry/geometry.h"
#include "geometry/geometry_set.h"


class Render {
    public:
        Render(SDL_Renderer* render) {
            _render = render;
        };
        void setColor(int r, int g, int b, int a);
        void clear();
        void present();
        void renderGeometrySet(GeometrySet* geometrySet);
        SDL_Renderer* sdlRender() { return _render; }

    private:
        SDL_Renderer* _render;
};

#endif
