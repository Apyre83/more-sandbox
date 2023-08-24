#include "Player.hpp"



Player::Player(int x, int y, sf::RenderWindow &window, sf::Vector2f& cellSize) : window(window), cellSize(cellSize) {
    _playerPos = {static_cast<float>(x), static_cast<float>(y)};
    _playerSize = {3, 2};
    _playerColor = sf::Color(255, 128, 0);

    _body = sf::RectangleShape(_playerSize);
    _body.setPosition(_playerPos);
    _body.setFillColor(_playerColor);

    _head = sf::RectangleShape(sf::Vector2f(1, 1));
    _head.setPosition({ _playerPos.x + 1, _playerPos.y - 1 });
    _head.setFillColor(sf::Color::White);
}


/*
 *  Check the last time the player moved and move him if it's been long enough in a random direction
 */
void    Player::update(std::vector<std::vector<int>> &cells) {
    if (_nbFramesUntilMove == 0) {
        int direction = rand() % 4;
        switch (direction) {
            case 0:
                if (_playerPos.x > 0 && cells[static_cast<int>(_playerPos.x - 1)][static_cast<int>(_playerPos.y)] == 0)
                    _playerPos.x--;
                break;
            case 1:
                if (_playerPos.x < NB_CELLS_X - 1 && cells[static_cast<int>(_playerPos.x + 1)][static_cast<int>(_playerPos.y)] == 0)
                    _playerPos.x++;
                break;
            case 2:
                if (_playerPos.y > 0 && cells[static_cast<int>(_playerPos.x)][static_cast<int>(_playerPos.y - 1)] == 0)
                    _playerPos.y--;
                break;
            case 3:
                if (_playerPos.y < NB_CELLS_Y - 1 && cells[static_cast<int>(_playerPos.x)][static_cast<int>(_playerPos.y + 1)] == 0)
                    _playerPos.y++;
                break;
            default:
                break;
        }
        // Next move between 30 and 90 frames
        _nbFramesUntilMove = rand() % 60 + 30;
    }
    else
        _nbFramesUntilMove--;
}


void    Player::draw(void) {
    /*_body.setPosition(_playerPos);
    _head.setPosition({ _playerPos.x + 1, _playerPos.y - 1 });
    _body.setFillColor(_playerColor);
    _head.setFillColor(sf::Color::White);
    window.draw(_body);
    window.draw(_head);*/

    // Pour l'instant, juste dessiner un gros rectangle sur la case correspondante
    sf::RectangleShape cell(sf::Vector2f(cellSize.x, cellSize.y));
    cell.setPosition({ _playerPos.x * cellSize.x, _playerPos.y * cellSize.y });
    cell.setFillColor(sf::Color(255, 128, 0));
    window.draw(cell);
}
