#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>

/// Serve como relogio e como temporizador
class Clock {
private:
    double _time; // em segundos
    bool _paused = false;
    double _timeout_duration; // em segundos (tempo que dura um timeout)

public:
    Clock();
    Clock(double time_duration);

    /// Incrementa o tempo por dt se nao estiver pausado, chama todo frame
    void update(double dt);

    /// Retorna o tempo em segundos
    double get_seconds_elapsed();

    /// Retorna o tempo em segundos e reseta a contagem
    double restart();

    /// Retorna true se ja deu o tempo (nao reseta a contagem)
    bool timeout();

    void pause();

    void resume();

    double get_timeout_duration();
};

#endif