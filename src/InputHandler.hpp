#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "Point.hpp"
#include "Constants.hpp"

class Game;

struct InputData
{
	bool m_rotate = false;
	int m_dx = 0;
	bool m_down = false;

	bool	hasInputs();
};

class GameInput
{
	public:
		GameInput(Game* pGame);
		~GameInput();

		void	keyPressed(sf::Keyboard::Key key);
		void	update(Point (&a)[4], Point (&b)[4]);
		void	move(Point (&a)[4], Point (&b)[4]);
		bool	check(Point (&a)[4], Point (&b)[4]);

	private:
		Game*		m_pGame;
		InputData	m_inputData;
};
