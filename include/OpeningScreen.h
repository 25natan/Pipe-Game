#pragma once
#include <SFML/Graphics.hpp>


class OpeningScreen
{
public:
	OpeningScreen(sf::RenderWindow& window,sf::Sprite& background);
	void show();
private:
	sf::RenderWindow& m_window;
	sf::Sprite& m_background;
	sf::Text m_pipeGameText;
};

