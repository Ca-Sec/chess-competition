#include "chess-simulator.h"
// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
#include "chess.hpp"
#include <random>

#include "board.h"
#include "piece.h"
#include "MinMaxBot.h"

using namespace ChessSimulator;

std::string ChessSimulator::Move(std::string fen) {
  // create your board based on the board string following the FEN notation
  // search for the best move using minimax / monte carlo tree search /
  // alpha-beta pruning / ... try to use nice heuristics to speed up the search
  // and have better results return the best move in UCI notation you will gain
  // extra points if you create your own board/move representation instead of
  // using the one provided by the library
    
  /*Board myBoard(fen);
  std::string myMove = Piece::getRandomMove(myBoard);
  return myMove;*/

  ////here goes a random movement
  //chess::Board board(fen);
  //chess::Movelist moves;
  //chess::movegen::legalmoves(moves, board);
  //if(moves.size() == 0)
  //  return "";

  //std::vector<std::string> uciMoves;

  //for (int i = 0; i <= moves.size() - 1; i++)
  //{
  //    uciMoves.push_back(chess::uci::moveToUci(moves[i]));
  //}

  ////// get random move
  //std::random_device rd;
  //std::mt19937 gen(rd());
  //std::uniform_int_distribution<> dist(0, moves.size() - 1);
  //auto move = moves[dist(gen)];
  //return chess::uci::moveToUci(move);

    MinMaxBot bot(3);
    return bot.getBestMove(fen);
}