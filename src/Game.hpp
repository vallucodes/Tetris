#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <memory>

#include "Constants.hpp"
#include "InputHandler.hpp"
#include "Point.hpp"

class Game : public sf::Drawable
{
	public:

		Game();
		~Game();

		bool	initialise();
		void	updateBlockState();
		void	draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		const sf::Font& getFont() const;
		const sf::Texture& getTiles() const;
		int			(&getFigures())[7][4];
		int&		getColorNum();
		sf::Clock&	getClock();
		float&		getTimer();
		float		getDelay();
		int			(&getField())[M][N];

		void	keyPressed(sf::Keyboard::Key key);

		void	newBlock(int& colorNum);
		void	clearFullRows();

	private:

		std::unique_ptr<GameInput> m_pGameInput;

		// game area
		int m_field[M][N] = {0};

		// block coordinates
		Point a[4], b[4];

		// block shapes
		int figures[7][4] =
		{
			1,3,5,7,
			2,4,5,7,
			3,5,4,6,
			3,5,4,7,
			2,3,5,7,
			3,5,7,6,
			2,3,4,5,
		};

		// clock
		float		m_timer = 0;
		float		m_delay = 0.2;
		sf::Clock	m_clock;

		// sprite movement
		// int		m_dx = 0;
		// bool	m_rotate = 0;
		int		m_colorNum = 1;

		// sprite textures and fonts
		sf::Font	m_font;
		sf::Texture	m_tiles;
		sf::Texture	m_wall;
};
