#include <SDL.h>
#include <SDL_render.h>
#include <list>

#include "geometry/geometry.h"
#include "geometry/geometry_set.h"
#include "geometry/line.h"
#include "geometry/ellipse.h"
#include "geometry/rectangle.h"
#include "geometry/parallelogram.h"
#include "geometry/triangle.h"
#include "button.h"
#include "render.h"
#include "drawer_state.h"
#include "shared/plugin_loader.h"
#include "marshal.h"


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Eremeev: Geometry OOP", 0, 0, 1024, 768, 0);
    if (!window) {
        return -1;
    }

    SDL_Renderer* SDL_render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!SDL_render) {
        return -1;
    }

    Render* render = new Render(SDL_render);
    DrawerState::SetMainRender(render);
    std::list<Button*> buttons;

    Plugin* colorizer = PluginLoader::LoadPlugin("shared/colorizer/colorizer.so");

    char running = 1;

    GeometrySet* figures = new GeometrySet();
    std::list<Geometry*>::iterator figuresIter = figures->itemsIterator();


    GeometrySet* buttonGeo;
    Button* button;

    buttonGeo = new GeometrySet();
    buttonGeo->add(new Rectangle(10, 10, 20, 20));
    buttonGeo->add(new Line(14, 26, 26, 14));
    button = new Button(10, 10, 30, 30, buttonGeo);
    button->onClick = [&](int x) {
        DrawerState::SetCurrentFigure(new Line(0, 0, 0, 0));
        DrawerState::SetState(DRAWER_SET_START_POINTS);
        figures->add(DrawerState::CurrentFigure());
    };
    buttons.push_back(button);

    buttonGeo = new GeometrySet();
    buttonGeo->add(new Rectangle(40, 10, 20, 20));
    buttonGeo->add(new Ellipse(50, 20, 8, 5));
    button = new Button(40, 10, 60, 30, buttonGeo);
    button->onClick = [&](int x) {
        DrawerState::SetCurrentFigure(new Ellipse(0, 0, 0, 0));
        DrawerState::SetState(DRAWER_SET_START_POINTS);
        figures->add(DrawerState::CurrentFigure());
    };
    buttons.push_back(button);

    buttonGeo = new GeometrySet();
    buttonGeo->add(new Rectangle(70, 10, 20, 20));
    buttonGeo->add(new Rectangle(74, 16, 12, 8));
    button = new Button(70, 10, 90, 30, buttonGeo);
    button->onClick = [&](int x) {
        DrawerState::SetCurrentFigure(new Rectangle(0, 0, 0, 0));
        DrawerState::SetState(DRAWER_SET_START_POINTS);
        figures->add(DrawerState::CurrentFigure());
    };
    buttons.push_back(button);

    buttonGeo = new GeometrySet();
    buttonGeo->add(new Rectangle(100, 10, 20, 20));
    buttonGeo->add(new Triangle(104, 16, 12, 8));
    button = new Button(100, 10, 120, 30, buttonGeo);
    button->onClick = [&](int x) {
        DrawerState::SetCurrentFigure(new Triangle(0, 0, 0, 0));
        DrawerState::SetState(DRAWER_SET_START_POINTS);
        figures->add(DrawerState::CurrentFigure());
    };
    buttons.push_back(button);

    buttonGeo = new GeometrySet();
    buttonGeo->add(new Rectangle(130, 10, 20, 20));
    buttonGeo->add(new Parallelogram(133, 16, 10, 8, 30));
    button = new Button(130, 10, 150, 30, buttonGeo);
    button->onClick = [&](int x) {
        DrawerState::SetCurrentFigure(new Parallelogram(0, 0, 0, 0, 0));
        DrawerState::SetState(DRAWER_SET_START_POINTS);
        figures->add(DrawerState::CurrentFigure());
    };
    buttons.push_back(button);


    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_TAB:
                        if (DrawerState::State() == DRAWER_IDLE) {
                            if (!figures->items()->empty()) {
                                if (figuresIter != figures->itemsIteratorEnd()) {
                                    (*figuresIter)->drop();
                                    figuresIter++;
                                }
                                if (figuresIter == figures->itemsIteratorEnd()) {
                                    figuresIter = figures->itemsIterator();
                                }
                                (*figuresIter)->take();
                                DrawerState::SetCurrentFigure(*figuresIter);
                            }
                        }
                        break;
                    case SDLK_m:
                        DrawerState::SetState(DRAWER_MOVE);
                        break;
                    case SDLK_x:
                        if (figuresIter != figures->itemsIteratorEnd()) {
                            (*figuresIter)->drop();
                        }
                        figuresIter = figures->itemsIteratorEnd();
                        DrawerState::SetCurrentFigure(NULL);
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_m:
                        DrawerState::SetState(DRAWER_IDLE);
                        break;
                    case SDLK_s:
                        serialize_to_file(figures);
                        break;
                    case SDLK_l:
                        deserialize_from_file(figures);
                        break;
                    default:
                        break;
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                switch (DrawerState::State()) {
                    case DRAWER_IDLE:
                        for (Button* btn : buttons) {
                            btn->handleMouseButton(event.button);
                        }
                        break;
                    case DRAWER_SET_START_POINTS:
                        DrawerState::CurrentFigure()->setStartPoints(event.button.x, event.button.y);
                        DrawerState::SetState(DRAWER_SET_FINISH_POINTS);
                        break;
                    case DRAWER_SET_FINISH_POINTS:
                        DrawerState::CurrentFigure()->setFinishPoints(event.button.x, event.button.y);
                        DrawerState::SetState(DRAWER_IDLE);
                        break;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                switch (DrawerState::State()) {
                    case DRAWER_SET_FINISH_POINTS:
                        DrawerState::CurrentFigure()->setFinishPoints(event.motion.x, event.motion.y);
                        break;
                    case DRAWER_MOVE:
                        if (
                            !figures->items()->empty() &&
                            figuresIter != figures->itemsIteratorEnd()
                        ) {
                            (*figuresIter)->move(event.motion.xrel, event.motion.yrel);
                        }
                        break;
                }
            } else if (event.type == SDL_QUIT) {
                running = 0;
            }

            colorizer->handleEvent(event);
        }

        render->setColor(0, 0, 0, 255);
        render->clear();

        render->renderGeometrySet(figures);

        for (Button* btn : buttons) {
            render->renderGeometrySet(btn->geometrySet());
        }

        colorizer->render();

        render->present();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    if (colorizer != NULL) { PluginLoader::Close(colorizer); }

    return 0;
}
