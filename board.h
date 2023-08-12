#pragma once

#include "move.h"
#include "player.h"
#include "pos.h"

#include <vector>

#define ST(X) static_cast<size_t>(X)

struct Board {
	Grid grid;
	const int size;

	Board(Grid const& grid);

	template<typename BOARD>
	bool operator==(BOARD&& other) const {
		return grid == other.grid;
	}

	void make_move(const Move move);

	std::vector<Pos> positions() const;

	Player result() const;

	void print() const;
};
