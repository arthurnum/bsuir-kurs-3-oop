#include "shared/plugin.h"

class Colorizer : public Plugin  {
    public:
        Colorizer(void* lib) : Plugin(lib) {};
        void handleEvent(SDL_Event event) override;
};

void Colorizer::handleEvent(SDL_Event event) {
    fprintf(stdout, "%d\n", event.type);
}

extern "C" Plugin* createPluginInstance(void* lib) {
    return new Colorizer(lib);
}
