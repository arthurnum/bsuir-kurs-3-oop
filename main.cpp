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

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Eremeev: Geometry OOP", 0, 0, 1024, 768, 0);
    if (!window) {
        return -1;
    }

    SDL_Renderer* SDL_render = SDL_CreateRenderer(window, -1, 0);
    if (!SDL_render) {
        return -1;
    }

    Render* render = new Render(SDL_render);
    std::list<Button*> buttons;

    char running = 1;

    GeometrySet* figures = new GeometrySet();

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

                    // Other input here
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
                }
            } else if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        render->setColor(0, 0, 0, 255);
        render->clear();

        render->setColor(255, 255, 255, 255);
        render->renderGeometrySet(figures);

        render->setColor(200, 200, 255, 255);
        for (Button* btn : buttons) {
            render->renderGeometrySet(btn->geometrySet());
        }

        render->present();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
