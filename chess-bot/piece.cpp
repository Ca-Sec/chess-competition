#include "piece.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"
#include "king.h"
#include <memory>
#include <random>

std::string Piece::getRandomMove(const Board& board) {
    std::vector<std::string> possibleMoves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            SquareContent piece = board.getPieceAt(row, col);
            if (piece == SquareContent::EMPTY) continue;

            PieceColor color = board.getTurn();

            bool isWhite = static_cast<int>(piece) <= static_cast<int>(SquareContent::WHITE_QUEEN);
            if ((color == PieceColor::WHITE && !isWhite) || (color == PieceColor::BLACK && isWhite))
                continue;

            std::unique_ptr<Piece> currentPiece;

            switch (piece) {
            case SquareContent::WHITE_PAWN:
            case SquareContent::BLACK_PAWN:
                currentPiece = std::make_unique<Pawn>(color, row, col);
                break;
            case SquareContent::WHITE_KNIGHT:
            case SquareContent::BLACK_KNIGHT:
                currentPiece = std::make_unique<Knight>(color, row, col);
                break;
            case SquareContent::WHITE_BISHOP:
            case SquareContent::BLACK_BISHOP:
                currentPiece = std::make_unique<Bishop>(color, row, col);
                break;
            case SquareContent::WHITE_ROOK:
            case SquareContent::BLACK_ROOK:
                currentPiece = std::make_unique<Rook>(color, row, col);
                break;
            case SquareContent::WHITE_QUEEN:
            case SquareContent::BLACK_QUEEN:
                currentPiece = std::make_unique<Queen>(color, row, col);
                break;
            case SquareContent::WHITE_KING:
            case SquareContent::BLACK_KING:
                currentPiece = std::make_unique<King>(color, row, col);
                break;
            default: break;
            }

            if (currentPiece) {
                auto legalMoves = currentPiece->getLegalMoves(board);
                for (const auto& move : legalMoves) {
                    possibleMoves.push_back(board.getMoveNotation(row, col, move.first, move.second));
                }
            }
        }
    }

    if (possibleMoves.empty()) {
        return "0000";
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleMoves.size() - 1);

    return possibleMoves[dist(gen)];
}
