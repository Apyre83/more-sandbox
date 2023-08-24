/*
 * The player is a 3x2 blue rectangle with his head a 1x1 white square
 */


#ifndef MORE_SANDBOX_PLAYER_HPP
#define MORE_SANDBOX_PLAYER_HPP

#include "sandbox.h"

class Player {
public:
    Player(int x, int y, sf::RenderWindow& window, sf::Vector2f& cellSize);
    ~Player() = default;

    void    draw(void);
    void    update(std::vector<std::vector<int>>& cells);

private:
    sf::RenderWindow&   window;
    sf::RectangleShape  _body;
    sf::RectangleShape  _head;
    sf::Vector2f        _playerPos;
    sf::Vector2f        _playerSize;
    sf::Color           _playerColor;

    sf::Vector2f        cellSize;

    int                 _nbFramesUntilMove = 0;
};

#endif //MORE_SANDBOX_PLAYER_HPP
