#include <iostream>
#include "SFML/Graphics.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");

int main() {
	// Snake
	sf::Texture snakeTexture;
	if (!snakeTexture.loadFromFile("./assets/snake.png")) {
		std::cout << "the image of snake could not be displayed :(" << std::endl;
		return 1;
	}
	sf::RectangleShape snake(sf::Vector2f(50, 50));
	snake.setTexture(&snakeTexture);

	//Dot
	sf::Texture dotTexture;
	if (!dotTexture.loadFromFile("./assets/dot.png")) {
		std::cout << "the image of dot could not be displayed :(" << std::endl;
	}
	sf::Sprite dot(dotTexture);
	dot.setScale(0.5, 0.5);
	dot.setPosition(150, 150);

	// Snake speed and boolean from collision
	float speed = 0.5f;
	bool collisionDetected = false;

	while(window.isOpen()) {
		// Game loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::Vector2f currentPosition = snake.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currentPosition.x + snake.getSize().x < window.getSize().x) {
			snake.move(speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currentPosition.x > 0) {
			snake.move(-speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentPosition.y > 0) {
			snake.move(0, -speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentPosition.y + snake.getSize().y < window.getSize().y) {
			snake.move(0, speed);
		}

		// Collision with Snake and Dot
		if (dot.getGlobalBounds().intersects(snake.getGlobalBounds())) {
			if (!collisionDetected) {
				std::cout << "Collision detected" << std::endl;
				collisionDetected = true;
			}
		}

		// Clean window, draw and show
		window.clear();
		window.draw(snake);
		window.draw(dot);
		window.display();
	}
	return 0;
}