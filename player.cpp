#include "player.h"

constexpr char CHAR_ARRAY[] = { 'O', 'X', '_' };

char to_char(const Player player) {
	return CHAR_ARRAY[static_cast<int>(player)];
}

constexpr double SCORE_ARRAY[] = { 1.0, -1.0, 0.0 };

double to_score(const Player player) {
	return SCORE_ARRAY[static_cast<int>(player)];
}


Player next_player(const Player player) {
	return player == Player::NOUGHTS ? Player::CROSSES : Player::NOUGHTS;
}
