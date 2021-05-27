#pragma once
#include "Tile.h"
class Sink:
    public Tile
{
public:
    Sink(std::pair<sf::Sprite, sf::Sprite> shapes, sf::Vector2f pos, std::vector<Direction> openTo)
        :Tile(shapes, pos, openTo) {}
};

