#pragma once
#include "RotatableTile.h"
class Tap :
    public RotatableTile
{
public:
    Tap(std::pair<sf::Sprite, sf::Sprite> shapes, sf::Vector2f pos, std::vector<Direction> openTo)
        :RotatableTile(shapes, pos, openTo) {}
};

