#ifndef UPGRADEUI_H
#define UPGRADEUI_H

#include "text_button.h"
#include "dissolving_text.h"
#include <SFML/Graphics/Text.hpp>
#include <string>

class UpgradeUI{
private:
    sf::Font _font;
    sf::Text _nome;
    int _preco;
    int _incremento;
    int _level;
    int _max_level;
    sf::Text _descricao;
    Room &_room;
    sf::Vector2f _position;
    sf::Rect <float> _colider;
    std::function<void()> _on_buy_callback;
    sf::Text _preco_text;
    sf::Text _level_label;
    sf::CircleShape _level_circle;
    DissolvingText _feedback_text;
public:
    UpgradeUI(std::string nome, int preco, int incremento, int level, int max_levels, std::string descricao,
        sf::Vector2f position, Room &room, std::function<void()> on_buy_callback);
    ~UpgradeUI();
    bool buy(const std::vector<sf::Event> &event_queue);
    void run(double dt, const std::vector<sf::Event> &event_queue);
    void draw();
    void reset_feedback();
    int get_level() const;
    void set_level(int level);
};

#endif