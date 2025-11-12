#ifndef HEALTH_MANAGER_H
#define HEALTH_MANAGER_H

#include <SFML/Graphics.hpp>
#include <functional>

class HealthManager {
private:
    int _max_life; // vida maxima
    int _life; // vida atual
    std::function<void()> _on_death_callback; // callback quando vida <= 0
public:
    HealthManager(int max_life, std::function<void()> on_death_callback);

    ~HealthManager();

    void set_life(int new_life);

    void set_max_life(int max_life);

    void set_on_death_callback(std::function<void()> on_death_callback);

    void decrease_life(int amount);

    int get_life() const;

	void increase_max_life(int amount); 

    void increase_life(int amount);

    /// Retorna true se a vida for <= 0
    bool is_dead();

    // So mostra se a vida nao estiver cheia.
    // Origem e o canto superior esquerdo Gabriel: Decidi botar origem customizavel para teste, mudo se precisar
    void draw_health_bar(sf::RenderWindow& window, sf::Vector2f position);
};

#endif