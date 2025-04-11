#include "rook.h"

std::vector<std::pair<int, int>> Rook::getLegalMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;
    const int directions[4][2] = {
        {-1, 0}, {1, 0},
        {0, -1}, {0, 1}
    };

    for (const auto& dir : directions) {
        int row = position.first;
        int col = position.second;

        while (true) {
            row += dir[0];
            col += dir[1];

            if (row < 0 || row >= 8 || col < 0 || col >= 8)
                break;

            SquareContent content = board.getPieceAt(row, col);

            if (content == SquareContent::EMPTY) {
                moves.emplace_back(row, col);
            }
            else {
                bool enemy =
                    (color == PieceColor::WHITE && static_cast<int>(content) >= static_cast<int>(SquareContent::BLACK_PAWN)) ||
                    (color == PieceColor::BLACK && static_cast<int>(content) <= static_cast<int>(SquareContent::WHITE_QUEEN) &&
                        content != SquareContent::EMPTY);

                if (enemy)
                    moves.emplace_back(row, col);
                break;
            }
        }
    }

    return moves;
}