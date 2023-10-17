#include <dlfcn.h>

#include "plugin.h"

typedef Plugin* (*createPluginInstanceFn)(void*);

class PluginLoader {
    public:
        static Plugin* LoadPlugin(const char * filename) {
            void* lib = dlopen(filename, RTLD_NOW);
            if (lib == NULL) {
                return NULL;
            }

            createPluginInstanceFn createPlugin = (createPluginInstanceFn)dlsym(lib, "createPluginInstance");
            Plugin* plugin = (*createPlugin)(lib);

            char *error;
            if ((error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", error);
                return NULL;
            }

            return plugin;
        };

        static void Close(Plugin* plugin) {
            dlclose(plugin->lib());
        }
};
