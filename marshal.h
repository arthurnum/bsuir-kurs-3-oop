#ifndef H_MARSHAL
#define H_MARSHAL

#include <cstdio>
#include <iterator>
#include <SDL.h>

#include "geometry/geometry.h"
#include "geometry/geometry_set.h"


void serialize_to_file(GeometrySet* figures) {
    FILE* file = fopen("geometry.dat", "wb");

    for (Geometry* item : *figures->items()) {
        unsigned char gtype = item->geometryType();
        fwrite(&gtype, sizeof(unsigned char), 1, file);

        int psize = item->getPointsCount();
        fwrite(&psize, sizeof(int), 1, file);

        SDL_Point* points = item->geometry();
        fwrite(points, sizeof(SDL_Point), psize, file);
    }

    fclose(file);
}

void deserialize_from_file(GeometrySet* figures) {
    FILE* file = fopen("geometry.dat", "rb");
    if (!file) { return; }

    figures->clear();
    while (!feof(file)) {
        unsigned char gtype;
        fread(&gtype, sizeof(unsigned char), 1, file);

        int psize;
        fread(&psize, sizeof(int), 1, file);

        SDL_Point points[psize];
        fread(points, sizeof(SDL_Point), psize, file);

        switch (gtype)
        {
            case GEOMETRY_ELLIPSE:
                figures->add(new Ellipse(psize, points));
                break;
            case GEOMETRY_LINE:
                figures->add(new Line(psize, points));
                break;
            case GEOMETRY_PARALLELOGRAM:
                figures->add(new Parallelogram(psize, points));
                break;
            case GEOMETRY_RECTANGLE:
                figures->add(new Rectangle(psize, points));
                break;
            case GEOMETRY_TRIANGLE:
                figures->add(new Triangle(psize, points));
                break;

            default:
                break;
        }
    }

    fclose(file);
}

#endif
