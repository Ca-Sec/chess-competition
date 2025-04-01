#include "board.h"
#include <sstream>
#include <vector>
#include <unordered_map>

Board::Board(std::string fen) {
    std::stringstream ss(fen);
    std::vector<std::string> splitFen;
    std::string token;

    while (std::getline(ss, token, ' ')) {
        splitFen.push_back(token);
    }

    parseBoardPosition(splitFen[0]);
    parseTurn(splitFen[1]);
    parseCastlingRights(splitFen[2]);
    parseEnPassantSquare(splitFen[3]);

    halfMoveClock = std::stoi(splitFen[4]);
    fullMoveNumber = std::stoi(splitFen[5]);
}

Board::~Board() {}

void Board::parseBoardPosition(const std::string& position) {
    static const std::unordered_map<char, SquareContent> pieceMap = {
        {'P', SquareContent::WHITE_PAWN}, {'p', SquareContent::BLACK_PAWN},
        {'R', SquareContent::WHITE_ROOK}, {'r', SquareContent::BLACK_ROOK},
        {'B', SquareContent::WHITE_BISHOP}, {'b', SquareContent::BLACK_BISHOP},
        {'K', SquareContent::WHITE_KING}, {'k', SquareContent::BLACK_KING},
        {'Q', SquareContent::WHITE_QUEEN}, {'q', SquareContent::BLACK_QUEEN}
    };

    uint8_t index = 0;
    for (char c : position) {
        if (pieceMap.count(c)) {
            setPiece(index++, pieceMap.at(c));
        }
        else if (std::isdigit(c)) {
            index += c - '0';
        }
    }
}

void Board::parseTurn(const std::string& turnStr) {
    turn = (turnStr == "w") ? PieceColor::WHITE : PieceColor::BLACK;
}

void Board::parseCastlingRights(const std::string& castlingStr) {
    castlingRights = 0;
    for (char c : castlingStr) {
        switch (c) {
        case 'K': castlingRights |= 0b1000; break;
        case 'Q': castlingRights |= 0b0100; break;
        case 'k': castlingRights |= 0b0010; break;
        case 'q': castlingRights |= 0b0001; break;
        }
    }
}

void Board::parseEnPassantSquare(const std::string& enPassantStr) {
    if (enPassantStr == "-") {
        enPassantSquare = 0;
    }
    else {
        enPassantSquare = (enPassantStr[0] - 'a' + 1) + (enPassantStr[1] - '1') * 8;
    }
}

void Board::setPiece(uint8_t index, SquareContent piece) {
    if (index < 64) {
        board[index] = piece;
    }
}

//std::vector<Piece*> Board::getPieces() const {
//    std::vector<Piece*> pieces;
//
//    for (int row = 0; row < 8; row++) {
//        for (int col = 0; col < 8; col++) {
//            Piece* piece = getPieceAt(row, col);
//            if (piece) {
//                pieces.push_back(piece);
//            }
//        }
//    }
//
//    return pieces;
//}