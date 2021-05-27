#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameClock
{
public:
	GameClock(sf::RenderWindow& window);
	void draw();
	void start();
private:
	sf::Clock m_clock;
	sf::Text m_timeTxt;
	sf::Font m_font;
	sf::RectangleShape m_frame;
	sf::RenderWindow& m_window;
};

