#include "visual_effect.h"

VisualEffect::VisualEffect(sf::Vector2f position, float radius, double duration, sf::Color color, Room& room)
    : _duration(duration), _start_color(color), _room(room) {

    _shape.setRadius(radius);
    _shape.setOrigin(radius, radius); // centraliza a origem
    _shape.setPosition(position);
    _shape.setFillColor(color);
}

void VisualEffect::run(double dt) {
    _timer.update(dt);

    double elapsed = _timer.get_seconds_elapsed();

    if (elapsed >= _duration) {
        _finished = true;
        return;
    }

    // calcula a opacidade baseada no tempo restante (efeito de fade out)
    float ratio = 1.0f - static_cast<float>(elapsed / _duration);
    sf::Color new_color = _start_color;
    new_color.a = static_cast<sf::Uint8>(_start_color.a * ratio);

    _shape.setFillColor(new_color);
}

void VisualEffect::draw() {
    _room.get_window().draw(_shape);
}

bool VisualEffect::is_finished() {
    return _finished;
}