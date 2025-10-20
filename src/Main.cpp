#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <iostream>

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "Constants.hpp"

int main(int argc, char* argv[])
{
	srand(time(0));
	ResourceManager::init(argv[0]);

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "lol xD");
	window.setKeyRepeatEnabled(true);

	Game pGame;
	if (!pGame.initialise())
	{
		std::cerr << "Game Failed to initialise" << std::endl;
		return 1;
	}

	pGame.newBlock(pGame.getColorNum());
	while (window.isOpen())
	{
		float time = pGame.getClock().getElapsedTime().asSeconds();
		pGame.getClock().restart();
		pGame.getTimer() += time;

		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up)
					pGame.keyPressed(event.key);
				else if (event.key.code == sf::Keyboard::Left)
					pGame.getDx() = -1;
				else if (event.key.code == sf::Keyboard::Right)
					pGame.getDx() = 1;
			}
		}
		pGame.updateBlockState();

		window.clear(sf::Color::Yellow);
		window.draw(pGame);
		window.display();
	}

	return 0;
}
