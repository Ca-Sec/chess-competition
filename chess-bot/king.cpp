#include "king.h"

std::vector<std::pair<int, int>> King::getLegalMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;

    int row = position.first;
    int col = position.second;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int newRow = row + dr;
            int newCol = col + dc;

            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                SquareContent target = board.getPieceAt(newRow, newCol);

                bool isEnemy =
                    (color == PieceColor::WHITE && static_cast<int>(target) >= static_cast<int>(SquareContent::BLACK_PAWN)) ||
                    (color == PieceColor::BLACK && static_cast<int>(target) <= static_cast<int>(SquareContent::WHITE_QUEEN) &&
                        target != SquareContent::EMPTY);

                if (target == SquareContent::EMPTY || isEnemy) {
                    moves.emplace_back(newRow, newCol);
                }
            }
        }
    }

    return moves;
}