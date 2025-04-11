#pragma once
#include "piece.h"

class King : public Piece {
public:
    King(PieceColor color, int row, int col) : Piece(color, row, col) {}
    std::vector<std::pair<int, int>> getLegalMoves(const Board& board) const override;
};