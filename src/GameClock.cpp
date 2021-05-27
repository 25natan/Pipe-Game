#include "GameClock.h"
GameClock::GameClock(sf::RenderWindow& window)
	:m_window(window)
{
	int txtSize = 60, spaceFromWindow = 40, frameWidth = 5, spaceFromFrame = 10;
	sf::Color color(0, 100, 0);

	//set font and text
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	m_timeTxt.setFont(m_font);
	m_timeTxt.setCharacterSize(txtSize);
	m_timeTxt.setString("Time  00:00");
	m_timeTxt.setFillColor(color);
	m_timeTxt.setPosition(spaceFromWindow,(m_window.getSize().y - txtSize) / 2);

	//set text frame
	m_frame.setSize(sf::Vector2f(m_timeTxt.getGlobalBounds().width + 2*spaceFromFrame,
		txtSize + 3*spaceFromFrame));
	m_frame.setPosition(m_timeTxt.getPosition().x - spaceFromFrame,
		m_timeTxt.getPosition().y - spaceFromFrame);
	m_frame.setOutlineThickness(frameWidth);
	m_frame.setOutlineColor(color);
}

void GameClock::start()
{
	m_clock.restart();
}

void GameClock::draw()
{
	int elapsedSeconds = (int)m_clock.getElapsedTime().asSeconds(),
		minuts = elapsedSeconds / 60, seconds = elapsedSeconds % 60;
	std::string str = minuts > 9 ? "Time  " + std::to_string(minuts) : "Time  0" + std::to_string(minuts);
	str += seconds > 9 ? ':'+std::to_string(seconds) : ":0" + std::to_string(seconds);

	m_timeTxt.setString(str);
	m_window.draw(m_frame);
	m_window.draw(m_timeTxt);
}