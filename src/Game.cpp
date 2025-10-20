#include "Game.hpp"
#include "ResourceManager.hpp"

#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

bool Game::initialise() {
	if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
	{
		std::cerr << "Unable to load font" << std::endl;
		return false;
	}
	if (!m_wall.loadFromFile(ResourceManager::getFilePath("tiles2_wall.png")))
	{
		std::cerr << "Unable to load font" << std::endl;
		return false;
	}
	if (!m_tiles.loadFromFile(ResourceManager::getFilePath("tiles2.png")))
	{
		std::cerr << "Unable to load texture" << std::endl;
		return false;
	}
	return true;
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	sf::Sprite tileWall(m_wall);
	sf::Sprite tile(m_tiles);

	int tilesX = ScreenWidth / tileSize;
	int tilesY = ScreenHeight / tileSize;

	// draw background
	for (int i = 0; i < tilesY; i++)
	{
		for (int j = 0; j < tilesX; j++)
		{
			if (j >= 2 && j <= tilesX - 3 && i >= 2 && i <= tilesY - 3)
				continue ;
			float posX = j * tileSize;
			float posY = i * tileSize;
			tileWall.setTextureRect(sf::IntRect(wallTile * tileSize,0,tileSize,tileSize));
			tileWall.setPosition(posX, posY);
			target.draw(tileWall);
		}
	}

	int offsetX = tilesX / 2;
	int offsetY = 2;
	// draw filled spaces
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (m_field[i][j] == 0)
				continue ;
			float posX = j * tileSize + 2 * tileSize;
			float posY = i * tileSize + offsetY * tileSize;
			// std::cout << "position filled: x: " << posX << "y: " << posY << std::endl;
			tile.setTextureRect(sf::IntRect(m_field[i][j] * tileSize,0,tileSize,tileSize));
			tile.setPosition(posX, posY);
			target.draw(tile);
		}
	}

	// draw flying piece
	for (int i = 0; i < 4; i++)
	{
		float posX = a[i].x * tileSize + 2 * tileSize;
		float posY = a[i].y * tileSize + offsetY * tileSize;
		tile.setTextureRect(sf::IntRect(m_colorNum * tileSize,0,tileSize,tileSize));
		tile.setPosition(posX, posY);
		target.draw(tile);
	}
}

const sf::Font& Game::getFont() const {
	return m_font;
}

const sf::Texture& Game::getTiles() const {
	return m_tiles;
}

int	(&Game::getFigures())[7][4] {
	return figures;
}

int&	Game::getDx() {
	return m_dx;
}

bool&	Game::getRotate() {
	return m_rotate;
}

int&	Game::getColorNum() {
	return m_colorNum;
}

sf::Clock&	Game::getClock() {
	return m_clock;
}

float&	Game::getTimer() {
	return m_timer;
}

float	Game::getDelay() {
	return m_delay;
}

void	Game::keyPressed(sf::Keyboard::Key key) {
	m_pGameInput->keyPressed(key);
}

void	Game::newBlock(int& colorNum) {
	colorNum = 1 + rand() % 7;
	// std::cout << "colorNum in Game: " << this->getColorNum() << std::endl;
	int n = colorNum - 1;
	// std::cout << "figure: " << n << std::endl;
	int offset = ScreenWidth / tileSize / 2;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2 + offset;
		a[i].y = figures[n][i] / 2;
	}
}

void	Game::updateBlockState() {
	m_pGameInput->update(a, b);
}

void	Game::clearFullRows() {
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (m_field[i][j] == 0)
				break ;
			if (j == N - 1)
			{
				// move one step lower every row above
				for (int k = i; k > 0; k--)
					for (int m = 0; m < N; m++)
						m_field[k][m] = m_field[k - 1][m];
			}
		}
	}
}
