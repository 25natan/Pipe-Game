#include "Tile.h"

Tile::Tile(pair<Sprite, Sprite> shapes, Vector2f pos, vector<Direction> openTo)
	:m_shapes(shapes),m_openTo(openTo)
{
	m_shapes.first.setPosition(pos);
	m_shapes.second.setPosition(pos);
}

void Tile::draw(RenderWindow& window)
{
	m_streamStatus ? window.draw(m_shapes.first) : window.draw(m_shapes.second);
}

void Tile::setNeighbors(Tile::Neighbors neighbors)
{
	m_neighbors = neighbors;
}

void Tile::setStream(bool flag)
{
	m_streamStatus = flag;
}

bool Tile::isStreamOn()
{
	return m_streamStatus;
}

vector<shared_ptr<Tile>> Tile::getNeighborsOpenTowards()
{
	vector<shared_ptr<Tile>> vec;
	if (m_neighbors.right && isOpenTo(Direction::Right) && m_neighbors.right->isOpenTo(Direction::Left))
		vec.push_back(m_neighbors.right);
	if (m_neighbors.left && isOpenTo(Direction::Left) && m_neighbors.left->isOpenTo(Direction::Right))
		vec.push_back(m_neighbors.left);
	if (m_neighbors.up && isOpenTo(Direction::Up) && m_neighbors.up->isOpenTo(Direction::Down))
		vec.push_back(m_neighbors.up);
	if (m_neighbors.down && isOpenTo(Direction::Down) && m_neighbors.down->isOpenTo(Direction::Up))
		vec.push_back(m_neighbors.down);
	return vec;
}

bool Tile::isOpenTo(Direction direction)
{
	for (auto dir : m_openTo)
		if (dir == direction)
			return true;
	return false;
}


sf::FloatRect Tile::getBounds()
{
	return m_shapes.first.getGlobalBounds();
}