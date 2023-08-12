#pragma once

#include "board.h"
#include "move.h"

#include <memory>
#include <unordered_map>
#include <vector>

#define HASH(X)\
{\
	size_t x = X;\
	x = ((x >> 16) ^ x) * 0x45d9f3b;\
	x = ((x >> 16) ^ x) * 0x45d9f3b;\
	x = (x >> 16) ^ x;\
	seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);\
}\

struct BoardHash {

	template<typename BOARD>
	size_t operator()(BOARD&& board) const {
		size_t seed = board.size;
		for (auto const& row : board.grid) {
			for (auto cell : row) {
				HASH(static_cast<size_t>(cell));
			}
		}
		return seed;
	}
};

enum class AlphaBetaFlag {
	UPPER,
	LOWER,
	EXACT,
};

struct LookupValue {
	double value;
	int level;
	AlphaBetaFlag flag;
	SharedMoves moves;

	LookupValue();

	LookupValue(const double value, const int level, const AlphaBetaFlag flag, const SharedMoves moves);
};

typedef std::unordered_map<Board, LookupValue, BoardHash> Lookup;
