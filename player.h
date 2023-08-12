#pragma once

#include <vector>

enum class Player {
	NOUGHTS,
	CROSSES,
	NEITHER,
};

typedef std::vector<Player> Row;
typedef std::vector<Row> Grid;

char to_char(const Player player);

double to_score(const Player player);

Player next_player(const Player player);
