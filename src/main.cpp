#include "sandbox.h"


std::map<int, std::pair<std::string, sf::Color>> buildings = {
    {0, {"Empty", sf::Color::Black}},
    {1, {"Wall", sf::Color::White}},
    {2, {"Player", sf::Color(255, 128, 0)}}, // Orange
    {3, {"Monster", sf::Color::Red}},
    {4, {"Weapon", sf::Color::Yellow}},
    {5, {"Potion", sf::Color::Magenta}},
    {6, {"Chest", sf::Color::Cyan}},
    {7, {"Door", sf::Color::Blue}},
    {8, {"Portal", sf::Color(128, 0, 128)}}, // Purple
    {9, {"Exit", sf::Color::Green}}
};

void    handleEvents(sf::RenderWindow& window, int& buildingMode, std::vector<std::vector<int>>& cells, bool& isPlaying, std::vector<Player>& players, sf::Vector2f& cellSize) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            window.close();

        // Start/stop simulation enter/space
        if ((event.type == sf::Event::KeyPressed) && ((event.key.code == sf::Keyboard::Enter) || (event.key.code == sf::Keyboard::Space))) {
            isPlaying = !isPlaying;
            if (isPlaying == true) {
                for (int i = 0; i < NB_CELLS_X; i++) {
                    for (int j = 0; j < NB_CELLS_Y; j++) {
                        if (cells[i][j] == 2) {
                            players.push_back(Player(i, j, window, cellSize));
                        }
                    }
                }
            }
            else players.clear();
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                buildingMode = (buildingMode + 1) % buildings.size();
            }
            else {
                buildingMode = (buildingMode - 1) % buildings.size();
            }
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R))
            cells = std::vector<std::vector<int>>(NB_CELLS_X, std::vector<int>(NB_CELLS_Y, 0));


        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num0)) buildingMode = 0;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) buildingMode = 1;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) buildingMode = 2;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3)) buildingMode = 3;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num4)) buildingMode = 4;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num5)) buildingMode = 5;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num6)) buildingMode = 6;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num7)) buildingMode = 7;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num8)) buildingMode = 8;
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num9)) buildingMode = 9;
    }
}



int main() {

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Game of Life", sf::Style::Fullscreen);
    sf::Vector2<float> desktopSize = { static_cast<float>(desktop.size.x), static_cast<float>(desktop.size.y) };

    window.setFramerateLimit(60);

    std::vector<std::vector<int>> cells(NB_CELLS_X, std::vector<int>(NB_CELLS_Y, 0));


    sf::Vector2<float> gridSize = { static_cast<float>(desktopSize.x * 0.70), desktopSize.y };
    sf::Vector2<float> cellSize = { gridSize.x / NB_CELLS_X, gridSize.y / NB_CELLS_Y };


    // Draw grid at the end to overwrite the cells printing
    sf::VertexArray lines(sf::PrimitiveType::Lines);
    for (int i = 0; i < NB_CELLS_X + 1; i++) {
        lines.append(sf::Vertex(sf::Vector2<float>(i * cellSize.x, 0), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2<float>(i * cellSize.x, gridSize.y), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2<float>(i * cellSize.x + 1, 0), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2<float>(i * cellSize.x + 1, gridSize.y), sf::Color::White));
    }
    for (int i = 0; i < NB_CELLS_Y + 1; i++) {
        lines.append(sf::Vertex(sf::Vector2<float>(0, i * cellSize.y), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2<float>(gridSize.x, i * cellSize.y), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2<float>(0, i * cellSize.y + 1), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2<float>(gridSize.x, i * cellSize.y + 1), sf::Color::White));
    }


    int     buildingMode = 0;
    bool    isPlaying = false;

    sf::Font font;
    if (!font.loadFromFile("res/race.ttf")) {
        std::cout << "Error loading font" << std::endl;
        return 1;
    }

    sf::Text buildingInfo(font);
    buildingInfo.setCharacterSize(24);
    buildingInfo.setFillColor(sf::Color::White);
    buildingInfo.setPosition({ gridSize.x + 10, 0 });

    sf::Text    simulationInfo(font);
    simulationInfo.setCharacterSize(24);
    simulationInfo.setFillColor(sf::Color::White);
    simulationInfo.setPosition({ gridSize.x + 10, 50 });


    // Store the players
    std::vector<Player> players;


    while (window.isOpen()) {

        handleEvents(window, buildingMode, cells, isPlaying, players, cellSize);

        for (auto& player : players) {
            player.update(cells);
        }

        if ((isPlaying == false) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window).x < gridSize.x) && (sf::Mouse::getPosition(window).y < gridSize.y))
            cells[static_cast<int>(sf::Mouse::getPosition(window).x / cellSize.x)][static_cast<int>(sf::Mouse::getPosition(window).y / cellSize.y)] = buildingMode;




        buildingInfo.setString("Building mode: " + buildings[buildingMode].first);
        simulationInfo.setString("Simulation: " + std::string(isPlaying ? "ON" : "OFF"));

        window.clear();

        if (isPlaying == false) drawNotPlaying(window, cellSize, cells, buildingMode);
        else drawPlaying(window, cellSize, cells, players);


        window.draw(lines);
        window.draw(buildingInfo);
        window.draw(simulationInfo);

        window.display();
    }

    return 0;
}

