#include <cmath>
#include <SDL_image.h>

#include "shared/plugin.h"

const int DRAWER_COLORIZER_ON = 100;
const int DRAWER_COLORIZER_CAPTURE = 101;

const double TWICE_PI = PI * 2;

class Colorizer : public Plugin  {
    public:
        Colorizer(void* lib) : Plugin(lib) {
            SDL_RWops* pngStream = SDL_RWFromFile("shared/colorizer/color-wheel.png", "r");
            SDL_Surface* colorWheel = IMG_LoadPNG_RW(pngStream);
            _texture = SDL_CreateTextureFromSurface(DrawerState::MainRender()->sdlRender(), colorWheel);
            SDL_FreeSurface(colorWheel);

            _targetRect.x = 0;
            _targetRect.y = 0;
            _targetRect.w = 128;
            _targetRect.h = 128;
        };
        void handleEvent(SDL_Event event) override;
        void render() override;

    private:
        int _x;
        int _y;
        SDL_Rect _targetRect;
        SDL_Texture* _texture;
};

void Colorizer::handleEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_c:
                if (DrawerState::State() == DRAWER_IDLE) {
                    DrawerState::SetState(DRAWER_COLORIZER_ON);
                }
                break;
            default:
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_c:
                if (DrawerState::State() == DRAWER_COLORIZER_ON || DrawerState::State() == DRAWER_COLORIZER_CAPTURE) {
                    DrawerState::SetState(DRAWER_IDLE);
                }
                break;
            default:
                break;
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (DrawerState::State() == DRAWER_COLORIZER_ON) {
            DrawerState::SetState(DRAWER_COLORIZER_CAPTURE);
            _x = event.button.x;
            _y = event.button.y;
            _targetRect.x = _x - 64;
            _targetRect.y = _y - 64;
        }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        if (DrawerState::State() == DRAWER_COLORIZER_ON || DrawerState::State() == DRAWER_COLORIZER_CAPTURE) {
            DrawerState::SetState(DRAWER_IDLE);
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        if (DrawerState::State() == DRAWER_COLORIZER_CAPTURE) {
            int dx = _x - event.button.x;
            int dy = _y - event.button.y;
            double D = sqrt(dx*dx + dy*dy);
            double angle = acos(dy / D);

            double colorAngle;

            if (dx <= 0) {
                colorAngle = angle;
            } else {
                colorAngle = PI + PI - angle;
            }

            int red = 0,
                green = 0,
                blue = 0;

            if (colorAngle >= 0 && colorAngle < (TWICE_PI / 6)) {
                red = 255;
                green = int(255 * colorAngle / (TWICE_PI / 6));

            } else if (colorAngle >= (TWICE_PI / 6) && colorAngle < (TWICE_PI * 2 / 6)) {
                double delta = colorAngle - (TWICE_PI / 6);
                green = 255;
                red = 255 - int(255 * delta / (TWICE_PI / 6));

            } else if (colorAngle >= (TWICE_PI * 2 / 6) && colorAngle < (TWICE_PI * 3 / 6)) {
                double delta = colorAngle - (TWICE_PI * 2 / 6);
                green = 255;
                blue = int(255 * delta / (TWICE_PI / 6));

            } else if (colorAngle >= (TWICE_PI * 3 / 6) && colorAngle < (TWICE_PI * 4 / 6)) {
                double delta = colorAngle - (TWICE_PI * 3 / 6);
                blue = 255;
                green = 255 - int(255 * delta / (TWICE_PI / 6));

            } else if (colorAngle >= (TWICE_PI * 4 / 6) && colorAngle < (TWICE_PI * 5 / 6)) {
                double delta = colorAngle - (TWICE_PI * 4 / 6);
                blue = 255;
                red = int(255 * delta / (TWICE_PI / 6));

            } else if (colorAngle >= (TWICE_PI * 5 / 6) && colorAngle < TWICE_PI) {
                double delta = colorAngle - (TWICE_PI * 5 / 6);
                red = 255;
                blue = 255 - int(255 * delta / (TWICE_PI / 6));
            }

            DrawerState::CurrentFigure()->setColor(red, green, blue);
        }
    }
}

void Colorizer::render() {
    if (DrawerState::State() == DRAWER_COLORIZER_CAPTURE) {
        SDL_RenderCopy(DrawerState::MainRender()->sdlRender(), _texture, NULL, &_targetRect);
    }
}

extern "C" Plugin* createPluginInstance(void* lib) {
    return new Colorizer(lib);
}
