#include "InputHandler.hpp"
#include "Game.hpp"

#include <iostream>

GameInput::GameInput(Game* pGame) : m_pGame(pGame) {}

GameInput::~GameInput() {}

void	GameInput::keyPressed(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Up)
		m_inputData.m_rotate = true;
	else if (key == sf::Keyboard::Left)
		m_inputData.m_dx -= 1;
	else if (key == sf::Keyboard::Right)
		m_inputData.m_dx += 1;
	else if (key == sf::Keyboard::Down)
		m_inputData.m_down = true;
}

void	GameInput::update(Point (&a)[4], Point (&b)[4]) {
	move(a, b);
}

void	GameInput::move(Point (&a)[4], Point (&b)[4]) {
	// move
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += m_inputData.m_dx;
	}
	// check if side is hit
	if (!check(a, b))
	{
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
	}

	// rotate
	if (m_inputData.m_rotate)
	{
		Point p = a[1];
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!check(a, b))
		{
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}
	}

	// tick
	if (m_pGame->getTimer() > m_pGame->getDelay())
	{
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].y += 1;
		}
		// check if bottom is hit
		if (!check(a, b))
		{
			for (int i = 0; i < 4; i++)
				m_pGame->getField()[b[i].y][b[i].x] = m_pGame->getColorNum();
			m_pGame->clearFullRows();
			m_pGame->newBlock(m_pGame->getColorNum());
		}
		m_pGame->getTimer() = 0;
	}

	std::cout << "dx: " << m_inputData.m_dx << std::endl;

	// reset helpers
	m_inputData.m_dx = 0;
	m_inputData.m_rotate = false;
	m_inputData.m_down = false;
}

bool	GameInput::check(Point (&a)[4], Point (&b)[4]) {
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return 0;
		else if (m_pGame->getField()[a[i].y][a[i].x])
			return 0;
	}
	return 1;
}

bool	InputData::hasInputs() {
	return (m_rotate || m_dx || m_down);
}

