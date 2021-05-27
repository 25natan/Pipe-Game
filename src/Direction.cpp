#include "Directions.h"
void rotateDirections(vector<Direction>& dirVec, Direction direction)
{
	if (direction == Direction::Left)
		for (auto& dir : dirVec)
			switch (dir)
			{
			case Direction::Right:dir = Direction::Up;
				break;
			case Direction::Up:dir = Direction::Left;
				break;
			case Direction::Left:dir = Direction::Down;
				break;
			case Direction::Down:dir = Direction::Right;
			}
	else if (direction == Direction::Right)
		for (auto& dir : dirVec)
			switch (dir)
			{
			case Direction::Right:dir = Direction::Down;
				break;
			case Direction::Up:dir = Direction::Right;
				break;
			case Direction::Left:dir = Direction::Up;
				break;
			case Direction::Down:dir = Direction::Left;
			}
}