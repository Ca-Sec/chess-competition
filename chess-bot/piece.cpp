#include "piece.h"

std::pair<int, int> Piece::getRandomMove(const Board& board) const {
    std::vector<std::pair<int, int>> legalMoves = getLegalMoves(board);
    if (legalMoves.empty()) return position;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, legalMoves.size() - 1);

    return legalMoves[dist(gen)];
}
