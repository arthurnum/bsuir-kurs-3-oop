```
clang++ -shared -I../../ -I/opt/homebrew/Cellar/sdl2/2.28.4/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.28.4/lib -L/opt/homebrew/Cellar/sdl2_image/2.6.3_2/lib -lSDL2 -lSDL2_image -fPIC -std=c++11 -o colorizer.so colorizer.cpp
```
