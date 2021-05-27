#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Bar {
	sf::RectangleShape rect;
	sf::Text txt;
	sf::Font font;
};

class StagesMenu
{
public:
	StagesMenu(sf::RenderWindow& window, sf::Sprite& background, int numOfStages);
	int show();
private:
	sf::RenderWindow& m_window;
	sf::Sprite& m_background;
	std::vector<Bar> m_bars;
	sf::Text m_chooseStageMsg;
	sf::Font font;
};

