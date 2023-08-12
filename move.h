#pragma once

#include "player.h"
#include "pos.h"

#include <memory>
#include <vector>

struct Move {
	Pos pos;
	Player player;
};

typedef std::vector<Move> Moves;
typedef std::shared_ptr<Moves> SharedMoves;
