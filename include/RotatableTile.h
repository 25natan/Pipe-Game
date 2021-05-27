#pragma once
#include "Tile.h"
class RotatableTile :
    public Tile
{
public:
    RotatableTile(std::pair<sf::Sprite, sf::Sprite> shapes, sf::Vector2f pos, std::vector<Direction> openTo);
    void rotate(int angle);
    virtual ~RotatableTile() = 0 {}
};

