#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int WIDTH = 800, HEIGHT = 600;
const int CELLSIZE = 10;
const int GRIDWIDTH = WIDTH / CELLSIZE, GRIDHEIGHT = HEIGHT / CELLSIZE;

void updateGrid(std::vector<std::vector<int>>& grid) {
    std::vector<std::vector<int>> newGrid = grid;

    for (int x = 0; x < GRIDWIDTH; ++x) {
        for (int y = 0; y < GRIDHEIGHT; ++y) {
            int aliveNeighbours = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int newX = x + dx, newY = y + dy;
                    if (newX >= 0 && newX < GRIDWIDTH && newY >= 0 && newY < GRIDHEIGHT) {
                        aliveNeighbours += grid[newX][newY];
                    }
                }
            }

            if (grid[x][y] == 1) {
                if (aliveNeighbours < 2 || aliveNeighbours > 3) {
                    newGrid[x][y] = 0;
                }
            } else {
                if (aliveNeighbours == 3) {
                    newGrid[x][y] = 1;
                }
            }
        }
    }

    grid = newGrid;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Game of Life");

    std::vector<std::vector<int>> grid(GRIDWIDTH, std::vector<int>(GRIDHEIGHT, 0));

    // Initial state
    // You can initialize grid with your own pattern
    grid[10][10] = 1;
    grid[11][11] = 1;
    grid[12][12] = 1;
    grid[12][11] = 1;
    grid[12][10] = 1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateGrid(grid);

        window.clear();
        for (int x = 0; x < GRIDWIDTH; ++x) {
            for (int y = 0; y < GRIDHEIGHT; ++y) {
                if (grid[x][y] == 1) {
                    sf::RectangleShape cell(sf::Vector2f(CELLSIZE, CELLSIZE));
                    cell.setPosition({ static_cast<float>(x * CELLSIZE), static_cast<float>(y * CELLSIZE) });
                    cell.setFillColor(sf::Color::White);
                    window.draw(cell);
                }
            }
        }
        window.display();

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}

