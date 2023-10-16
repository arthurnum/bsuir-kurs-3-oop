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
        setColor(figure->color()[0], figure->color()[1], figure->color()[2], 255);
        SDL_RenderDrawLines(_render, figure->geometry(), figure->getPointsCount());
    }
}
