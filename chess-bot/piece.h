#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>
#include <random>
#include "board.h"

class Piece {
protected:
    PieceColor color;
    std::pair<int, int> position;

public:
    Piece(PieceColor color, int row, int col) : color(color), position(row, col) {}
    virtual ~Piece() = default;

    virtual std::vector<std::pair<int, int>> getLegalMoves(const Board& board) const = 0;
    static std::string getRandomMove(const Board& board);
};

#endif
