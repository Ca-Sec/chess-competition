#include "pawn.h"

std::vector<std::pair<int, int>> Pawn::getLegalMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;

    int dir = (color == PieceColor::WHITE) ? -1 : 1;
    int startRow = (color == PieceColor::WHITE) ? 6 : 1;

    int row = position.first;
    int col = position.second;

    if (board.getPieceAt(row + dir, col) == SquareContent::EMPTY) {
        moves.emplace_back(row + dir, col);

        if (row == startRow && board.getPieceAt(row + 2 * dir, col) == SquareContent::EMPTY) {
            moves.emplace_back(row + 2 * dir, col);
        }
    }

    for (int dc : {-1, 1}) {
        int newCol = col + dc;
        int newRow = row + dir;

        if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {
            SquareContent target = board.getPieceAt(newRow, newCol);

            bool enemy =
                (color == PieceColor::WHITE && static_cast<int>(target) >= static_cast<int>(SquareContent::BLACK_PAWN)) ||
                (color == PieceColor::BLACK && static_cast<int>(target) <= static_cast<int>(SquareContent::WHITE_QUEEN) &&
                    target != SquareContent::EMPTY);

            if (enemy)
                moves.emplace_back(newRow, newCol);
        }
    }

    return moves;
}