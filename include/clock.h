#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>

class Clock {
private:
    double _time = 0; // em segundos
    bool _paused = false;

public:
    /// Incrementa o tempo por dt se nao estiver pausado, chama todo frame
    void update(double dt);

    /// Retorna o tempo em segundos
    double get_seconds_elapsed();

    /// Retorna o tempo em segundos e reseta a contagem
    double restart();

    void pause();

    void resume();
};

#endif