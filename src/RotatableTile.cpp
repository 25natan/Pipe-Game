#include "RotatableTile.h"

RotatableTile::RotatableTile(std::pair<sf::Sprite, sf::Sprite> shapes, sf::Vector2f pos, std::vector<Direction> openTo)
	:Tile(shapes, pos, openTo)
{}

void RotatableTile::rotate(int angle)
{
	m_shapes.first.rotate(angle);
	m_shapes.second.rotate(angle);
	if (angle == 90)
		rotateDirections(m_openTo, Direction::Right);
	else
		rotateDirections(m_openTo, Direction::Left);
}


