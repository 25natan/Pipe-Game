#include "Stage.h"
const int TILE_SIZE = 120;
Stage::Stage(vector<string>& charBoard, Resources& resources, RenderWindow& window, Sprite& background)
	:m_resources(resources),m_window(window),m_background(background),
	m_clock(window), m_clicksCounter(window)
{
	checkStageChars(charBoard);
	m_board = vector<vector<shared_ptr<Tile>>>(charBoard.size(),vector< shared_ptr<Tile>>(charBoard[0].size()));
	Vector2f startLocation = locateInWindow();

	//set objects	
	for (size_t i = 0;i < charBoard.size();i++)
		for (size_t j = 0;j < charBoard[0].size();j++)
		{
			Vector2f pos(startLocation.x + TILE_SIZE / 2 + j * TILE_SIZE,
				startLocation.y + TILE_SIZE / 2 + i * TILE_SIZE);
			pair<Sprite, Sprite> shapes;
			vector<Direction> opens;

			//set shapes and direction
			if (charBoard[i][j] == PIPE_CROSS) {
				shapes.first.setTexture(m_resources.pipeCrossOn);
				shapes.second.setTexture(m_resources.pipeCrossOff);
				opens = vector<Direction>{ Direction::Up,Direction::Right,Direction::Down,Direction::Left };
			}
			else if (charBoard[i][j] <= PIPE_STREIGHT_1) {
				shapes.first.setTexture(m_resources.pipeStreightOn);
				shapes.second.setTexture(m_resources.pipeStreightOff);
				opens = vector<Direction>{ Direction::Right,Direction::Left };
			}
			else if (charBoard[i][j] <= PIPE_CURVED_3) {
				shapes.first.setTexture(m_resources.pipeCurvedOn);
				shapes.second.setTexture(m_resources.pipeCurvedOff);
				opens = vector<Direction>{ Direction::Right,Direction::Down };
			}
			else if (charBoard[i][j] <= PIPE_T_3) {
				shapes.first.setTexture(m_resources.pipeTon);
				shapes.second.setTexture(m_resources.pipeToff);
				opens = vector<Direction>{ Direction::Left,Direction::Up,Direction::Right };
			}
			else if (charBoard[i][j] <= TAP_3) {
				shapes.first.setTexture(m_resources.tap);
				shapes.second.setTexture(m_resources.tap);
				opens = vector<Direction>{ Direction::Up };
			}
			else {
				shapes.first.setTexture(m_resources.sinkOn);
				shapes.second.setTexture(m_resources.sinkOff);
				opens = vector<Direction>{ Direction::Up };
			}
			

			//set origin to center
			shapes.first.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
			shapes.second.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);

			//rotate shapes and direction if needed
			if (charBoard[i][j] == PIPE_STREIGHT_1 || charBoard[i][j] == PIPE_CURVED_1 || charBoard[i][j] == PIPE_T_1 ||
				charBoard[i][j] == SINK_1 || charBoard[i][j] == TAP_1) {
				shapes.first.rotate(90);
				shapes.second.rotate(90);
				rotateDirections(opens, Direction::Right);
			}
			if (charBoard[i][j] == PIPE_CURVED_2 || charBoard[i][j] == PIPE_T_2 || charBoard[i][j] == SINK_2 ||
				charBoard[i][j] == TAP_2) {
				shapes.first.rotate(180);
				shapes.second.rotate(180);
				rotateDirections(opens, Direction::Right);
				rotateDirections(opens, Direction::Right);
			}
			if (charBoard[i][j] == PIPE_CURVED_3 || charBoard[i][j] == PIPE_T_3 || charBoard[i][j] == SINK_3 ||
				charBoard[i][j] == TAP_3){
				shapes.first.rotate(270);
				shapes.second.rotate(270);
				rotateDirections(opens, Direction::Left);
			}

			//costruct objects
			if (charBoard[i][j] <= PIPE_T_3) {
				m_rotatableTiles.push_back(make_shared<Pipe>(shapes, pos, opens));
				m_board[i][j] = m_rotatableTiles.back();
			}
			else if (charBoard[i][j] <= TAP_3) {
				m_taps.push_back(make_shared<Tap>(shapes, pos, opens));
				m_rotatableTiles.push_back(m_taps.back());
				m_board[i][j] = m_taps.back();
			}
			else {
				m_sinks.push_back(make_shared<Sink>(shapes, pos, opens));
				m_board[i][j] = m_sinks.back();
			}
		}

	//set stage frame
	int farmeSize = 15;
	sf::Color color(0, 100, 0);
	m_frame.setSize(Vector2f(m_board[0].size()* TILE_SIZE, m_board.size()* TILE_SIZE));
	m_frame.setPosition(m_board[0][0]->getBounds().left, m_board[0][0]->getBounds().top);
	m_frame.setOutlineThickness(farmeSize);
	m_frame.setOutlineColor(color);
	m_frame.setFillColor(sf::Color::Transparent);

	//set every tile's neighbors
	setTileNeighbors();
}

void Stage::setTileNeighbors()
{
	Tile::Neighbors nib;
	for (size_t i = 0;i < m_board.size();i++)
		for (size_t j = 0;j < m_board[0].size();j++)
		{
			nib.up = i > 0 ? m_board[i - 1][j] : NULL;
			nib.down = i < m_board.size() - 1 ? m_board[i + 1][j] : NULL;
			nib.right = j < m_board[0].size() - 1 ? m_board[i][j + 1] : NULL;
			nib.left = j > 0 ? m_board[i][j - 1] : NULL;
			m_board[i][j]->setNeighbors(nib);
		}
}

void Stage::play()
{
	m_clock.start();
	while (m_window.isOpen())
	{
		resetStreamOff();
		//set stream on and starting from all the taps
		for (auto tap : m_taps)
			conectStream(tap);
		drawStage();
		if (allSinksGotWater())
			break;
		userRotate();
	}
	finishStage();
}

Vector2f Stage::locateInWindow()
{
	return Vector2f((m_window.getSize().x-TILE_SIZE*m_board[0].size())/2,
		(m_window.getSize().y - TILE_SIZE * m_board[0].size()) / 3);
}

void Stage::userRotate()
{
	while (m_window.isOpen())
	{
		drawStage();
		sf::Event ev;
		if (m_window.pollEvent(ev))
			if (ev.type == sf::Event::Closed)
				m_window.close();
			else if (ev.type == sf::Event::MouseButtonPressed)
				for (auto tile : m_rotatableTiles)
					if (tile->getBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
					{
						ev.mouseButton.button == sf::Mouse::Left?tile->rotate(90):tile->rotate(-90);
						m_clicksCounter.raise();
						return;
					}
	}
}

void Stage::drawStage()
{
	//clear the window and then draw the all board
	m_window.clear();
	m_window.draw(m_background);
	m_clock.draw();
	m_clicksCounter.draw();
	for (auto row : m_board)
		for (auto tile : row)
			if (tile)
				tile->draw(m_window);
	m_window.draw(m_frame);
	m_window.display();
}

void Stage::conectStream(shared_ptr<Tile> tile)
{
	tile->setStream(true);
	std::vector<shared_ptr<Tile>> neighbors = tile->getNeighborsOpenTowards();
	for(auto neighbor: neighbors)
		if(!(neighbor->isStreamOn()))
			conectStream(neighbor);
}

bool Stage::allSinksGotWater()
{
	for (auto sink : m_sinks)
		if (!(sink->isStreamOn()))
			return false;
	return true;
}

void Stage::resetStreamOff()
{
	//set all stream off
	for (auto tiles : m_board)
		for (auto tile : tiles)
			tile->setStream(false);
}

void Stage::finishStage()
{
	//wait some time befor clear the last stage situation
	sf::Clock clock;
	while (m_window.isOpen() && clock.getElapsedTime().asSeconds() < 0.5)
	{
		sf::Event ev;
		if (m_window.pollEvent(ev) && ev.type == sf::Event::Closed)
			m_window.close();
	}

	//set baravo text
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	sf::Text txt("Bravo!!", font, 250);
	txt.setFillColor(sf::Color(0, 100, 0));
	txt.setPosition((m_window.getSize().x - txt.getGlobalBounds().width) / 2,
		(m_window.getSize().y - txt.getGlobalBounds().height) / 3);

	//show text on screen for some seconds
	clock.restart();
	while (m_window.isOpen() && clock.getElapsedTime().asSeconds() < 3)
	{
		m_window.clear();
		m_window.draw(m_background);
		m_window.draw(txt);
		m_window.display();
		sf::Event ev;
		if (m_window.pollEvent(ev) && ev.type == sf::Event::Closed)
			m_window.close();
	}
}


void Stage::checkStageChars(vector<string>& charBoard)
{
	if (!charBoard.size())
		throw string("Empty stage!");
	int row = charBoard.front().size();
	for (auto str : charBoard)
		if (str.size() != row)
			throw string("Stage is not k*n characters!");
	for(auto str : charBoard)
		for(auto ch:str)
			switch (ch)
			{
			case PIPE_CROSS:
			case PIPE_STREIGHT_0:
			case PIPE_STREIGHT_1:
			case PIPE_CURVED_0:
			case PIPE_CURVED_1:
			case PIPE_CURVED_2:
			case PIPE_CURVED_3:
			case PIPE_T_0:
			case PIPE_T_1:
			case PIPE_T_2:
			case PIPE_T_3:
			case TAP_0:
			case TAP_1:
			case TAP_2:
			case TAP_3:
			case SINK_0:
			case SINK_1:
			case SINK_2:
			case SINK_3:
				break;
			default:
				throw string("One or more characters are not valid!");
			}
}
