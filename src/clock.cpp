#include "clock.h"

Clock::Clock(): _time(0), _timeout_duration(0) {}
Clock::Clock(double time_duration): _time(0), _timeout_duration(time_duration) {}

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

bool Clock::timeout() {
    return _time > _timeout_duration;
}

void Clock::pause() {
    _paused = true;
}

void Clock::resume() {
    _paused = false;
}

double Clock::get_timeout_duration() {
    return _timeout_duration;
}

void Clock::set_timeout_duration(double timeout_duration) {
    _timeout_duration = timeout_duration;
}