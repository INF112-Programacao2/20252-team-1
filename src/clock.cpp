#include "clock.h"

void Clock::update(double dt) {
    if (!_paused)
        _time += dt;
}

double Clock::get_seconds_elapsed() {
    return _time;
}

double Clock::restart() {
    double ret = _time;
    _time = 0;

    return ret;
}

void Clock::pause() {
    _paused = true;
}

void Clock::resume() {
    _paused = false;
}