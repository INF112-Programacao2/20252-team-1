#ifndef UPGRADEUI_H
#define UPGRADEUI_H

#include "text_button.h"
#include <SFML/Graphics/Text.hpp>
#include <string>

class UpgradeUI{
private:
    sf::Font _font;
    sf::Text _nome;
    int _preco;
    int _level;
    sf::Text _descricao;
    Room &_room;
    sf::Vector2f _position;
    sf::Rect <float> _colider;
public:
    UpgradeUI(std::string nome, int preco, int level, std::string descricao, sf::Vector2f position, Room &room);
    ~UpgradeUI();
    bool buy(const std::vector<sf::Event> &event_queue);
    void run(double dt, const std::vector<sf::Event> &event_queue);
    void draw();
};

#endif