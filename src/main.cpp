#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::VideoMode 	desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u	desktopSize = desktop.size;
	float			ratio = static_cast<float>(desktopSize.x) / static_cast<float>(desktopSize.y);

    sf::RenderWindow window(desktop, "more-sandbox", sf::Style::Fullscreen);

	int	gridWidth = 100;
	int	gridHeight = gridWidth * ratio;
	int	nbGridWidth = desktopSize.x / gridWidth;
	int	nbGridHeight = desktopSize.y / gridHeight;
	int	nbGrid = nbGridWidth - nbGridHeight;

    sf::VertexArray verticalLines(sf::PrimitiveType::Lines);
	sf::Vector2f p1, p2, p3, p4;

	// Draw the first line to not draw it twice
	p1 = {0, 0};
	p2 = {static_cast<float>(desktopSize.x), static_cast<float>(desktopSize.y)};
	verticalLines.append(sf::Vertex(p1, sf::Color(255, 128, 0)));
	verticalLines.append(sf::Vertex(p2, sf::Color(255, 128, 0)));


	// Do the same for other diagonals
	p1 = {0, static_cast<float>(desktopSize.y)};
	p2 = {static_cast<float>(desktopSize.x), 0};
	verticalLines.append(sf::Vertex(p1, sf::Color(255, 128, 0)));
	verticalLines.append(sf::Vertex(p2, sf::Color(255, 128, 0)));


	std::cout << "nbGridWidth: " << nbGridWidth << std::endl;
	std::cout << "nbGridHeight: " << nbGridHeight << std::endl;
	std::cout << "nbGrid: " << nbGrid << std::endl;
	std::cout << "ratio: " << ratio << std::endl;

	for (int i = 1; i < nbGrid; ++i) {
		p1 = {static_cast<float>(i * gridHeight), 0};
		p2 = {static_cast<float>(desktopSize.x), static_cast<float>(desktopSize.y) - i * gridWidth};
		verticalLines.append(sf::Vertex(p1, sf::Color::Red));
		verticalLines.append(sf::Vertex(p2, sf::Color::Red));

		p1 = {0, static_cast<float>(i * gridWidth)};
		p2 = {static_cast<float>(desktopSize.x) - i * gridHeight, static_cast<float>(desktopSize.y)};
		verticalLines.append(sf::Vertex(p1, sf::Color::Red));
		verticalLines.append(sf::Vertex(p2, sf::Color::Red));

		p1 = {static_cast<float>(i * gridHeight), 0};
		p2 = {0, static_cast<float>(i * gridWidth)};
		verticalLines.append(sf::Vertex(p1, sf::Color::Red));
		verticalLines.append(sf::Vertex(p2, sf::Color::Red));

		p1 = {static_cast<float>(desktopSize.x), static_cast<float>(desktopSize.y) - i * gridWidth};
		p2 = {static_cast<float>(desktopSize.x) - i * gridHeight, static_cast<float>(desktopSize.y)};
		verticalLines.append(sf::Vertex(p1, sf::Color::Red));
		verticalLines.append(sf::Vertex(p2, sf::Color::Red));
	}

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();

			//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) playerY--;
			//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) playerY++;
			//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) playerX--;
			//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) playerX++;
        }

        window.clear();
        window.draw(verticalLines);
        window.display();
    }

    return 0;
}

