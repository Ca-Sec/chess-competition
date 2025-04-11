#pragma once
#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(PieceColor color, int row, int col) : Piece(color, row, col) {}
    std::vector<std::pair<int, int>> getLegalMoves(const Board& board) const override;
};