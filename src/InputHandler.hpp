#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "Point.hpp"
#include "Constants.hpp"

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
		GameInput();
		~GameInput();

		void	keyPressed(sf::Keyboard::Key key);
		void	update(Point (&a)[4], Point (&b)[4]);
		void	move(Point (&a)[4], Point (&b)[4]);
		bool	check(Point (&a)[4], Point (&b)[4]);

	private:
		InputData	m_inputData;
};
