#pragma once
#include "piece.h"

class Rook : public Piece {
public:
	Rook(PieceColor color, int row, int col) : Piece(color, row, col) {}
	std::vector<std::pair<int, int>> getLegalMoves(const Board& board) const override;
};