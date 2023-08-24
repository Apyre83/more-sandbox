#ifndef MORE_SANDBOX_SANDBOX_H
#define MORE_SANDBOX_SANDBOX_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>

class Player;

#include "Player.hpp"

#define NB_CELLS_X 40
#define NB_CELLS_Y 40
#define BORDER_WIDTH 1


extern std::map<int, std::pair<std::string, sf::Color>> buildings;

void    drawNotPlaying(sf::RenderWindow& window, sf::Vector2f& gridSize, std::vector<std::vector<int>>& cells, int& buildingMode);
void    drawPlaying(sf::RenderWindow& window, sf::Vector2f& cellSize, std::vector<std::vector<int>>& cells, std::vector<Player>& players);


#endif //MORE_SANDBOX_SANDBOX_H
