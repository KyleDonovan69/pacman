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

	void movePacman();
	void moveGhost();
	
	void setupFontAndText();
	void setupSprite();

	const float MAX_DOTS = 17;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::CircleShape circles[17];
	sf::CircleShape pacman;
	
	sf::RectangleShape ghost;
	sf::RectangleShape borderTop;
	sf::RectangleShape borderBottom;

	int m_direction = 1;


	float pacmanX = 10;
	float pacmanY = 245;

	float posx = 10.0;
	float posy = 255.0;
	float width = 800.0;
	float height = 40.0;
	float radius = 15;
	int previous = 0;
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

