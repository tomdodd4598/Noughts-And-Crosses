#include "board.h"
#include "lookup.h"
#include "move.h"
#include "node.h"
#include "player.h"

#include <iostream>
#include <limits>
#include <vector>

int main() {
	constexpr int SIZE = 4;
	constexpr int DEPTH = 16;

	std::cout << "Solving...\n";

	auto root = Node(Board(Grid(SIZE, Row(SIZE, Player::NEITHER))));
	const auto result = root.negamax(Player::NOUGHTS, DEPTH);

	std::cout << "Evaluation: " << result << '\n';
	std::cout << "Nodes: " << node_count << '\n';

	Board board = root.board;
	for (auto const& move : *root.moves) {
		board.make_move(move);
		board.print();
	}
}
