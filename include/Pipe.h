#pragma once
#include "RotatableTile.h"

class Pipe :
    public RotatableTile
{
public:
    Pipe(pair<Sprite, Sprite> shapes, Vector2f pos, vector<Direction> openTo)
        :RotatableTile(shapes,pos, openTo) {}
};

