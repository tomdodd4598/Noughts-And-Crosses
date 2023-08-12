#pragma once

#include "board.h"
#include "lookup.h"
#include "move.h"
#include "player.h"

#include <memory>
#include <vector>

extern size_t node_count;

struct Node {
	const Board board;
	SharedMoves moves;

	Node(Board&& board);

	std::unique_ptr<Node> next(const Move move) const;

	double heuristic(const Player player) const;

	double negamax(const Player player, const int depth);

	double alphabeta(const Player player, const int level, double alpha, double beta);
};
