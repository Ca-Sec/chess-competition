#pragma once
#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(PieceColor color, int row, int col) : Piece(color, row, col) {}
    std::vector<std::pair<int, int>> getLegalMoves(const Board& board) const override;
};