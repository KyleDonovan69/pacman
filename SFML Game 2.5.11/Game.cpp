/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>
#include <ctime>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	srand(time(nullptr));
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	makeDots();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		speed *= -1;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	timer += t_deltaTime.asSeconds();
	m_time.setString("Timer: " + std::to_string(static_cast <int> (timer)));
	m_scoreMsg.setString("Score" + std::to_string(score));
	pacmanX += speed;
	pacman.setPosition(pacmanX, pacmanY);
	ghost.setPosition(ghostX, 245);

	if (!timerRunning) {//creates timer
		powerUpTimer.restart();//resets timer for pacman
		timerRunning = true;
	}

	if (pacmanX == borderLeft)
	{
		pacmanX = borderRight;
	}
	else if (pacmanX == borderRight)
	{
		pacmanX = borderLeft;
	}

	if (ghostX == borderLeft)
	{
		ghostX = borderRight;
	}
	else if (ghostX == borderRight)
	{
		ghostX = borderLeft;
	}

	if (powerUP == false)
	{
		if (ghostX > pacmanX)
		{
			ghostX -= ghostSpeed;
		}
		else
		{
			ghostX += ghostSpeed;
		}
	}
	else
	{
		if (ghostX > pacmanX)
		{
			ghostX += ghostSpeed;
		}
		else
		{
			ghostX -= ghostSpeed;
		}
	}


	for (int i = 0; i < MAX_DOTS; i++)
	{
		if (pacman.getGlobalBounds().intersects(circles[i].getGlobalBounds()))
		{
			circles[i].setPosition(0, 0);
			circles[i].setFillColor(sf::Color::Transparent);
			score++;
		}
		else if (pacman.getGlobalBounds().intersects(circles[berryLocation].getGlobalBounds()))
		{
			circles[berryLocation].setPosition(0, 0);
			circles[berryLocation].setFillColor(sf::Color::Transparent);
			score + 5;
			ghost.setFillColor(sf::Color::Blue);
			powerUP = true;
			count++;
			powerUpTimer.restart();

		}

		if (count == MAX_DOTS)
		{
			makeDots();
		}
	}

		if (powerUpTimer.getElapsedTime().asSeconds() >= 5.0f)//does this after certain time
		{
			ghost.setFillColor(sf::Color::Red);
			powerUP = false;
		}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < MAX_DOTS; i++)
	{
		m_window.draw(circles[i]);
	}
	m_window.draw(m_time);
	m_window.draw(m_scoreMsg);
	m_window.draw(m_title);
	m_window.draw(borderTop);
	m_window.draw(borderBottom);
	m_window.draw(ghost);
	m_window.draw(pacman);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_time.setFont(m_ArialBlackfont);
	m_time.setString("Timer" + std::to_string(timer));
	m_time.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_time.setPosition(40.0f, 40.0f);
	m_time.setCharacterSize(20U);
	m_time.setOutlineColor(sf::Color::Red);
	m_time.setFillColor(sf::Color::White);
	m_time.setOutlineThickness(3.0f);

	m_scoreMsg.setFont(m_ArialBlackfont);
	m_scoreMsg.setString("Score" + std::to_string(score));
	m_scoreMsg.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_scoreMsg.setPosition(700.0f, 40.0f);
	m_scoreMsg.setCharacterSize(20U);
	m_scoreMsg.setOutlineColor(sf::Color::Red);
	m_scoreMsg.setFillColor(sf::Color::White);
	m_scoreMsg.setOutlineThickness(3.0f);

	m_title.setFont(m_ArialBlackfont);
	m_title.setString("NOT PACMAN");
	m_title.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_title.setPosition(250.0f, 40.0f);
	m_title.setCharacterSize(40U);
	m_title.setOutlineColor(sf::Color::Red);
	m_title.setFillColor(sf::Color::Black);
	m_title.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);


}

void Game::makeDots()
{
	//int berryLocation = (rand() % MAX_DOTS) + 1;

	for (int i = 0; i < MAX_DOTS; i++)
	{
		circles[i].setPosition(posx, posy);
		
		circles[i].setRadius(radius);
		if (i == berryLocation)
		{
			circles[berryLocation].setRadius(20);
			circles[berryLocation].setPosition(posx - 4, posy - 4);
		}
		circles[i].setFillColor(sf::Color::Green);

		posx = posx + 50;
	}

	pacman.setPosition(pacmanX, pacmanY);
	pacman.setRadius(25);
	pacman.setFillColor(sf::Color::Yellow);

	borderTop.setSize(sf::Vector2f(width, height));
	borderTop.setPosition(0, 200);
	borderTop.setFillColor(sf::Color::Blue);

	borderBottom.setSize(sf::Vector2f(width, height));
	borderBottom.setPosition(0, 300);
	borderBottom.setFillColor(sf::Color::Blue);

	ghost.setSize(sf::Vector2f(50, 50));
	ghost.setPosition(ghostX, 245);
	ghost.setFillColor(sf::Color::Red);
}

