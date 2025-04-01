#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <cstdint>

enum class SquareContent {
    EMPTY,
    WHITE_PAWN, BLACK_PAWN,
    WHITE_ROOK, BLACK_ROOK,
    WHITE_BISHOP, BLACK_BISHOP,
    WHITE_KING, BLACK_KING,
    WHITE_QUEEN, BLACK_QUEEN
};

enum class PieceColor {
    WHITE,
    BLACK
};

class Board {
public:
    explicit Board(std::string fen);
    ~Board();

    //std::vector<Piece*> getPieces() const;

private:
    void parseBoardPosition(const std::string& position);
    void parseTurn(const std::string& turnStr);
    void parseCastlingRights(const std::string& castlingStr);
    void parseEnPassantSquare(const std::string& enPassantStr);

    void setPiece(uint8_t index, SquareContent piece);

    SquareContent board[64] = { SquareContent::EMPTY };
    PieceColor turn;
    uint8_t castlingRights;
    uint8_t enPassantSquare;
    int halfMoveClock;
    int fullMoveNumber;
};

#endif