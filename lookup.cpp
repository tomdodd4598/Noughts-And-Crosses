#include "lookup.h"
#include "move.h"

#include <memory>
#include <vector>

LookupValue::LookupValue() : LookupValue(0.0, 0, static_cast<AlphaBetaFlag>(0), SharedMoves{}) {}

LookupValue::LookupValue(const double value, const int level, const AlphaBetaFlag flag, const SharedMoves moves) : value{ value }, level{ level }, flag{ flag }, moves{ moves } {}
