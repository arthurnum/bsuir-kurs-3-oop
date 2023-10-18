#ifndef H_PLUGIN
#define H_PLUGIN

#include <SDL.h>

#include "../drawer_state.h"

class Plugin {
    public:
        Plugin(void* lib) { _lib = lib; }
        virtual void handleEvent(SDL_Event event) = 0;
        virtual void render() = 0;
        void* lib() { return _lib; }

    protected:
        void* _lib;
};


#endif
