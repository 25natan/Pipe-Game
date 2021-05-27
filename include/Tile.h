#pragma once
#include <SFML/Graphics.hpp>
#include "Directions.h"
#include <utility>
#include <memory>
using std::shared_ptr;
using sf::Sprite;
using std::vector;
using std::pair;
using sf::Vector2f;
using sf::RenderWindow;

class Tile
{
public:
	Tile(pair<Sprite, Sprite> shapes,Vector2f pos, vector<Direction> openTo);
	void draw(RenderWindow& window);
	vector<shared_ptr<Tile>> getNeighborsOpenTowards();
	void setStream(bool flag);
	bool isStreamOn();
	bool isOpenTo(Direction direction);
	struct Neighbors {
		shared_ptr<Tile> up, right, down, left;
	};
	void setNeighbors(Neighbors neighbors);
	sf::FloatRect getBounds();
	virtual ~Tile() = 0 {}
protected:
	pair<Sprite, Sprite> m_shapes;
	vector<Direction> m_openTo;
	Neighbors m_neighbors;
	bool m_streamStatus;
};

