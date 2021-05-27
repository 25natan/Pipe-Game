#include "StagesMenu.h"
StagesMenu::StagesMenu(sf::RenderWindow& window, sf::Sprite& background, int numOfStages)
	:m_window(window),m_background(background)
{
	//size for bars, texts and spaces between
	int barSize = 150,
		barFrameSize = 10,
		txtSize = 130,
		spaceSize = 100,
		barsInRow = 4;

	//color for the bars and texts
	sf::Color color(0, 100, 0);

	//loading font for text
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	//set choose stage massage
	m_chooseStageMsg.setFont(font);
	m_chooseStageMsg.setCharacterSize(txtSize);
	m_chooseStageMsg.setString("Please choose a stage!");
	m_chooseStageMsg.setPosition((m_window.getSize().x - m_chooseStageMsg.getGlobalBounds().width) / 2,0);
	m_chooseStageMsg.setFillColor(color);

	//set the bars vector to size like number of stages
	//with bars in barSize*barSize size and text 
	//in txtSize size
	m_bars = std::vector<Bar>(numOfStages,
		Bar{ sf::RectangleShape(sf::Vector2f(barSize,barSize)),sf::Text("",font,txtSize) });

	//set the start position of the bars rows
	//to the middle in x and one bar space in y
	sf::Vector2f startPos((m_window.getSize().x - barsInRow * barSize - (barsInRow - 1) * spaceSize) / 2,
		barSize+ spaceSize);

	//set thickness size for the bars
	//and color and position for the bars and texts
	for (size_t i(0);i < m_bars.size();i++)
	{
		m_bars[i].rect.setOutlineThickness(barFrameSize);
		m_bars[i].rect.setOutlineColor(color);
		m_bars[i].rect.setPosition(startPos.x + (i% barsInRow) * (barSize + spaceSize),
			startPos.y + (i / barsInRow) * (barSize + spaceSize));
		m_bars[i].txt.setString(std::to_string(i + 1));
		m_bars[i].txt.setFillColor(color);
		m_bars[i].txt.setPosition(m_bars[i].rect.getGlobalBounds().left + barSize / 3,
			m_bars[i].rect.getGlobalBounds().top);
	}
}

int StagesMenu::show()
{
	sf::Event ev;
	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.draw(m_background);
		m_window.draw(m_chooseStageMsg);
		for (auto bar : m_bars)
		{
			m_window.draw(bar.rect);
			std::string str = bar.txt.getString();
			m_window.draw(bar.txt);
		}
		m_window.display();
		if (m_window.pollEvent(ev))
			if (ev.type == sf::Event::Closed)
				m_window.close();
			else if (ev.type == sf::Event::MouseButtonPressed)
				for (size_t i(0);i < m_bars.size();i++)
					if (m_bars[i].rect.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						return i;
	}
	return -1;
}