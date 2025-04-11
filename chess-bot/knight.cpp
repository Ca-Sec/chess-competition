#include "knight.h"

std::vector<std::pair<int, int>> Knight::getLegalMoves(const Board& board) const {
	std::vector<std::pair<int, int>> moves;
	const int offsets[8][2] = {
		{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
		{1, -2}, {1, 2}, {2, -1}, {2, 1}
	};

	for (const auto& offset : offsets) {
		int newRow = position.first + offset[0];
		int newCol = position.second + offset[1];

		if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
			auto content = board.getPieceAt(newRow, newCol);
			if (content == SquareContent::EMPTY ||
				(color == PieceColor::WHITE && static_cast<int>(content) >= static_cast<int>(SquareContent::BLACK_PAWN)) ||
				(color == PieceColor::BLACK && static_cast<int>(content) <= static_cast<int>(SquareContent::WHITE_QUEEN) &&
					content != SquareContent::EMPTY)) {
				moves.emplace_back(newRow, newCol);
			}
		}
	}

	return moves;
}