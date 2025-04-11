#pragma once
#include "piece.h"

class Queen : public Piece {
public:
    Queen(PieceColor color, int row, int col) : Piece(color, row, col) {}
    std::vector<std::pair<int, int>> getLegalMoves(const Board& board) const override;
};