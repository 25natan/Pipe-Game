#include "OpeningScreen.h"
OpeningScreen::OpeningScreen(sf::RenderWindow& window, sf::Sprite& backgraound)
	:m_window(window),m_background(backgraound)
{}
	
void OpeningScreen::show()
{
	//clock for the opening screen delay
	sf::Clock clock;

	//create Pipe Game text to print in the opening screen
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Text pipeGameText("Pipe Game", font, 300);
	sf::Color color(0, 100, 0);
	pipeGameText.setFillColor(color);
	pipeGameText.setPosition((m_window.getSize().x - pipeGameText.getGlobalBounds().width) / 2,
		(m_window.getSize().y - pipeGameText.getGlobalBounds().height) / 4);

	//draw and display the background and the title for some seconds
	while (m_window.isOpen() && clock.getElapsedTime().asSeconds() < 3)
	{
		m_window.clear();
		m_window.draw(m_background);
		m_window.draw(pipeGameText);
		m_window.display();
		sf::Event ev;
		if (m_window.pollEvent(ev) && ev.type == sf::Event::Closed)
			m_window.close();
	}
}