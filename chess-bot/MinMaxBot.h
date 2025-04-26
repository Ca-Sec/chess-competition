#pragma once
#include <string>
#include "chess.hpp"

class MinMaxBot
{
public:
	MinMaxBot(int depth = 3);
	std::string getBestMove(const std::string& fen);

private:
	int minimax(chess::Board& board, int depth, bool maximizingPlay, int alpha, int beta);
	int evaluateBoard(const chess::Board& board);
	int evaluateMove(const chess::Move& move, const chess::Board& board);

	int m_depth;
};