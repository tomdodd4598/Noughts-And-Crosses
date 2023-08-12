#include "board.h"
#include "move.h"
#include "node.h"
#include "player.h"

#include <iostream>
#include <utility>
#include <vector>

Board::Board(Grid const& grid) : grid{ grid }, size{ static_cast<int>(grid.size()) } {}

void Board::make_move(const Move move) {
	grid[move.pos.row][move.pos.col] = move.player;
}

#define PUSH(I, J)\
{\
	const auto cell = grid[I][J];\
	if (cell == Player::NEITHER) {\
		vec.push_back(Pos(I, J));\
	}\
}\

std::vector<Pos> Board::positions() const {
	std::vector<Pos> vec{};
	const auto hsize = size / 2;
	
	if (size & 1) {
		PUSH(hsize, hsize);
	}
	for (int i = 0; i < hsize; ++i) {
		const auto j = static_cast<int>(ST(size) - i - 1);
		PUSH(i, i);
		PUSH(i, j);
		PUSH(j, i);
		PUSH(j, j);
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (i != j && i + j + 1 != size) {
				PUSH(i, j);
			}
		}
	}

	return vec;
}

#define RESULT_LINE(I, J, X, Y, GOTO)\
if ((cell = grid[X][Y]) != Player::NEITHER) {\
	for (int j = 1; j < size; ++j) {\
		if (cell != grid[I][J]) {\
			goto GOTO;\
		}\
	}\
	return cell;\
}\

Player Board::result() const {
	Player cell;
	for (int i = 0; i < size; ++i) {
		RESULT_LINE(i, j, i, 0, next1);
	next1: {}
	}
	for (int i = 0; i < size; ++i) {
		RESULT_LINE(j, i, 0, i, next2);
	next2: {}
	}
	RESULT_LINE(j, j, 0, 0, next3);
next3:
	RESULT_LINE(j, ST(size) - j - 1, 0, ST(size) - 1, finish);
finish:
	return Player::NEITHER;
}

void Board::print() const {
	for (auto const& row : grid) {
		for (auto cell : row) {
			std::cout << to_char(cell);
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
}
