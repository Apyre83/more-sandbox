#include "sandbox.h"


void    drawNotPlaying(sf::RenderWindow& window, sf::Vector2f& cellSize, std::vector<std::vector<int>>& cells, int& buildingMode) {

    sf::Vector2<float> mousePos = { static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
    sf::Vector2<float> cellPos = { static_cast<float>(static_cast<int>(mousePos.x / cellSize.x)), static_cast<float>(static_cast<int>(mousePos.y / cellSize.y)) };

    sf::RectangleShape mouseCell(cellSize);
    mouseCell.setPosition({ cellPos.x * cellSize.x, cellPos.y * cellSize.y});
    mouseCell.setFillColor(buildings[buildingMode].second);


    // Draw each cell according to its value
    for (int i = 0; i < NB_CELLS_X; i++) {
        for (int j = 0; j < NB_CELLS_Y; j++) {
            sf::RectangleShape cell(cellSize);
            cell.setPosition({ i * cellSize.x, j * cellSize.y });
            cell.setFillColor(buildings[cells[i][j]].second);
            window.draw(cell);
        }
    }

    window.draw(mouseCell);
}

void    drawPlaying(sf::RenderWindow& window, sf::Vector2f& cellSize, std::vector<std::vector<int>>& cells ,std::vector<Player>& players) {
    // Draw each cell according to its value
    for (int i = 0; i < NB_CELLS_X; i++) {
        for (int j = 0; j < NB_CELLS_Y; j++) {
            if (cells[i][j] == 1) {
                sf::RectangleShape cell(cellSize);
                cell.setPosition({ i * cellSize.x, j * cellSize.y });
                cell.setFillColor(buildings[cells[i][j]].second);
                window.draw(cell);
            }
        }
    }
    for (auto& player : players) {
        player.draw();
    }
}