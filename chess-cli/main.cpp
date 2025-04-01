#include "chess-simulator.h"
#include "chess.hpp"
#include "board.h"
#include "piece.h"
#include <string>
#include <iostream>

int main() {
    std::string fen;
    getline(std::cin, fen);

    Board board(fen);
    
    /*std::vector<Piece*> pieces = board.getPieces();

    for (auto piece : pieces) {
        std::vector<std::pair<int, int>> moves = piece->getLegalMoves(board);
        if (!moves.empty()) {
            auto move = piece->getRandomMove(board);
            std::cout << "Move: " << move.first << "," << move.second << std::endl;
            break;
        }
    }*/

    return 0;
}
