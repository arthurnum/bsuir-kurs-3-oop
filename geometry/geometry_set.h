#ifndef H_GEOMETRY_SET
#define H_GEOMETRY_SET

#include <list>

#include "geometry.h"

class GeometrySet {
    public:
        void add(Geometry* item) { _items.push_back(item); };
        std::list<Geometry*>* items() { return &_items; }
        std::list<Geometry*>::iterator itemsIterator() { return _items.begin(); }
        std::list<Geometry*>::iterator itemsIteratorEnd() { return _items.end(); }

    protected:
        std::list<Geometry*> _items;
};

#endif
