#include "board.h"
#include "lookup.h"
#include "node.h"
#include "player.h"

#include <algorithm>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

double constexpr INF = std::numeric_limits<double>::infinity();
double constexpr NaN = std::numeric_limits<double>::quiet_NaN();

size_t node_count = 0;

Lookup lookup{};

Node::Node(Board&& board) : board{ std::move(board) }, moves{ std::make_shared<Moves>() } {}

std::unique_ptr<Node> Node::next(const Move move) const {
	Board next = board;
	next.make_move(move);
	return std::make_unique<Node>(std::move(next));
}

#define HEURISTIC_LINE(I, J)\
{\
	auto noughts = 0, crosses = 0;\
	for (int j = 0; j < size; ++j) {\
		const auto cell = grid[I][J];\
		if (cell == Player::NOUGHTS) {\
			++noughts;\
		}\
		else if (cell == Player::CROSSES) {\
			--crosses;\
		}\
	}\
	value += noughts == 0 ? crosses : (crosses == 0 ? noughts : 0);\
}\

double Node::heuristic(const Player player) const {
	double value = 0.0;
	const auto size = board.size;
	auto const& grid = board.grid;

	for (int i = 0; i < size; ++i) {
		HEURISTIC_LINE(i, j);
		HEURISTIC_LINE(j, i);
	}
	HEURISTIC_LINE(j, j);
	HEURISTIC_LINE(j, ST(size) - j - 1);

	return value * to_score(player);
}

double Node::negamax(const Player player, const int depth) {
	node_count = 0;
	lookup.clear();
	return alphabeta(player, depth, -INF, INF);
}

double Node::alphabeta(const Player player, const int level, double alpha, double beta) {
	++node_count;

	const double alpha_original = alpha;

	const auto search = lookup.find(board);
	LookupValue entry;
	if (search != lookup.end()) {
		entry = search->second;
		if (entry.level >= level) {
			if (entry.flag == AlphaBetaFlag::UPPER) {
				beta = std::min(beta, entry.value);
			}
			else if (entry.flag == AlphaBetaFlag::LOWER) {
				alpha = std::max(alpha, entry.value);
			}

			if (entry.flag == AlphaBetaFlag::EXACT || alpha >= beta) {
				moves = entry.moves;
				return entry.value;
			}
		}
	}

	const auto result = board.result();
	if (result != Player::NEITHER) {
		return player == result ? INF : -INF;
	}
	else if (level == 0) {
		return heuristic(player);
	}

	const auto positions = board.positions();
	if (positions.empty()) {
		return 0.0;
	}

	const auto child_player = next_player(player);
	const auto child_level = level - 1;
	auto value = NaN;

	Move best_move = Move();
	std::unique_ptr<Node> best_node;
	for (auto const& pos : positions) {
		auto const cand_move = Move(pos, player);
		auto cand_node = next(cand_move);
		const double cand_value = -cand_node->alphabeta(child_player, child_level, -beta, -alpha);
		if (std::isnan(value) || value < cand_value) {
			value = cand_value;
			best_move = cand_move;
			best_node = std::move(cand_node);
		}
		alpha = std::max(alpha, value);
		if (alpha >= beta) {
			break;
		}
	}

	if (best_node) {
		moves->push_back(best_move);
		moves->insert(moves->end(), best_node->moves->begin(), best_node->moves->end());
	}

	entry = LookupValue(value, level, value <= alpha_original ? AlphaBetaFlag::UPPER : (value >= beta ? AlphaBetaFlag::LOWER : AlphaBetaFlag::EXACT), moves);
	lookup.insert({ board, entry });

	return value;
}
