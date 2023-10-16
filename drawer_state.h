#ifndef H_DRAWER_STATE
#define H_DRAWER_STATE

#include "geometry/geometry.h"

const int DRAWER_IDLE = 0;
const int DRAWER_SET_START_POINTS = 1;
const int DRAWER_SET_FINISH_POINTS = 2;

class DrawerState {
    protected:
        DrawerState() {
            _state = DRAWER_IDLE;
        };
        static DrawerState* _instance;
        int _x;
        int _state;
        Geometry* _currentFigure;

        static DrawerState* getInstance() {
            if (_instance == nullptr) {
                _instance = new DrawerState();
            }
            return _instance;
        }

    public:
        static int X() { return getInstance()->_x; }
        static int State() { return getInstance()->_state; }
        static Geometry* CurrentFigure() { return getInstance()->_currentFigure; }

        static void SetState(int state) { getInstance()->_state = state; }
        static void SetCurrentFigure(Geometry* figure) { getInstance()->_currentFigure = figure; }
};

DrawerState* DrawerState::_instance = nullptr;

#endif
