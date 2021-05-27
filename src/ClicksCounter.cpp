#include "ClicksCounter.h"

ClicksCounter::ClicksCounter(sf::RenderWindow& window)
	:m_window(window),m_counter(0)
{
	int txtSize = 60, spaceFromWindow = 40, frameWidth = 5, spaceFromFrame = 10;
	sf::Color color(0, 100, 0);

	//set font and text
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	m_countTxt.setFont(m_font);
	m_countTxt.setCharacterSize(txtSize);
	m_countTxt.setString("Clicks       ");
	m_countTxt.setFillColor(color);
	m_countTxt.setPosition(m_window.getSize().x - spaceFromWindow- m_countTxt.getGlobalBounds().width,
		(m_window.getSize().y - txtSize) / 2);

	//set text frame
	m_frame.setSize(sf::Vector2f(m_countTxt.getGlobalBounds().width + 2 * spaceFromFrame,
		txtSize + 3 * spaceFromFrame));
	m_frame.setPosition(m_countTxt.getPosition().x - spaceFromFrame,
		m_countTxt.getPosition().y - spaceFromFrame);
	m_frame.setOutlineThickness(frameWidth);
	m_frame.setOutlineColor(color);
}

void ClicksCounter::raise()
{
	m_counter++;
}


void ClicksCounter::draw()
{
	m_countTxt.setString("Clicks " + std::to_string(m_counter));
	m_window.draw(m_frame);
	m_window.draw(m_countTxt);
}