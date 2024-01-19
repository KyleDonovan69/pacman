/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void makeDots();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();

	static const int MAX_DOTS = 17;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	sf::Text m_time;
	sf::Text m_scoreMsg;

	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::CircleShape circles[MAX_DOTS];
	sf::CircleShape powerUp;
	sf::CircleShape pacman;
	
	sf::RectangleShape ghost;
	sf::RectangleShape borderTop;
	sf::RectangleShape borderBottom;

	int score = 0;
	float timer = 0.0;

	int berryLocation = (rand() % MAX_DOTS) + 1;

	int speed = 1;
	float ghostSpeed = 1.2;

	float pacmanX = 10;
	float pacmanY = 245;

	float ghostX = 750;

	int borderLeft = 0;
	int borderRight = 800;

	float posx = 10.0;
	float posy = 255.0;
	float width = 800.0;
	float height = 40.0;
	float radius = 15;
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

