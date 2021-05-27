#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ClicksCounter
{
public:
	ClicksCounter(sf::RenderWindow& window);
	void raise();
	void draw();
private:
	sf::Text m_countTxt;
	sf::Font m_font;
	sf::RectangleShape m_frame;
	sf::RenderWindow& m_window;
	int m_counter;
};

