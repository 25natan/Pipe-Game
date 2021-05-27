#pragma once
#include <vector>
using std::vector;

enum class Direction { Up, Down, Right, Left };
void rotateDirections(vector<Direction>& dirVec, Direction direction);