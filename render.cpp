#include "render.h"

void Render::clear() {
    SDL_RenderClear(_render);
}

void Render::present() {
    SDL_RenderPresent(_render);
}

void Render::setColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(_render, r, g, b, a);
}

void Render::renderGeometrySet(GeometrySet* geometrySet) {
    for (Geometry* figure : *geometrySet->items()) {
        SDL_Point* points = figure->geometry();
        int r = figure->color()[0],
            g = figure->color()[1],
            b = figure->color()[2];
        int width = figure->active() ? 2 : 1;
        for (int i = 0; i < figure->getPointsCount() - 1; i++) {
            thickLineRGBA(_render, points[i].x, points[i].y, points[i+1].x, points[i+1].y, width, r, g, b, 255);
        }
    }
}
