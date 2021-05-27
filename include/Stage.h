#pragma once
#include "Pipe.h"
#include "Tap.h"
#include "Sink.h"
#include "Tile.h"
#include "GameClock.h"
#include "ClicksCounter.h"
#include "Directions.h"
#include "TilesChar.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <memory>
#include <string>
using std::shared_ptr;
using std::make_shared;
using sf::Sprite;
using std::vector;
using std::pair;
using sf::Vector2f;
using sf::RenderWindow;
using std::string;



class Stage
{
public:
	Stage(vector<string>& charBoard, Resources& resources, RenderWindow& window,Sprite& background);
	void play();

private:
	void checkStageChars(vector<string>& charBoard);
	void userRotate();
	void setTileNeighbors();
	void conectStream(shared_ptr<Tile> tile);
	void drawStage();
	bool allSinksGotWater();
	void resetStreamOff();
	Vector2f locateInWindow();
	void finishStage();
	vector<vector<shared_ptr<Tile>>> m_board;
	vector< shared_ptr<RotatableTile>> m_rotatableTiles;
	vector< shared_ptr<Sink>> m_sinks;
	vector< shared_ptr<Tap>> m_taps;
	Resources& m_resources;
	RenderWindow& m_window;
	Sprite& m_background;
	sf::RectangleShape m_frame;
	GameClock m_clock;
	ClicksCounter m_clicksCounter;
};

