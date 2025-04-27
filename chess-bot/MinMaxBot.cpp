#include "MinMaxBot.h"
#include <vector>
#include <random>
#include <algorithm>

MinMaxBot::MinMaxBot(int depth)
	: m_depth(depth)
{ }

// Move Ordering Attempt
int MinMaxBot::evaluateMove(const chess::Move& move, const chess::Board& board)
{
	chess::Board tempBoard = board;
	tempBoard.makeMove(move);
	return evaluateBoard(tempBoard);
}

// Tries to find best move out of all current legal moves
std::string MinMaxBot::getBestMove(const std::string& fen)
{
	chess::Board board(fen);
	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	if (moves.size() == 0)
		return "";

	int bestScore = -100000;
	chess::Move bestMove;

	// Returns moves in the "best" move order
	std::sort(moves.begin(), moves.end(), [&](const chess::Move& move1, const chess::Move& move2) {
		return evaluateMove(move1, board) > evaluateMove(move2, board);
		});

	// Runs through all current legal moves with MinMax
	for (auto move : moves)
	{
		board.makeMove(move);
		int score = minimax(board, m_depth - 1, false, -100000, 100000);
		board.unmakeMove(move);

		if (score > bestScore)
		{
			bestScore = score;
			bestMove = move;
		}
	}

	return chess::uci::moveToUci(bestMove);
}

// MinMax Algorithm using alpha-beta prunning
int MinMaxBot::minimax(chess::Board& board, int depth, bool maximizingPlay, int alpha, int beta)
{
	if (depth == 0 || board.isGameOver().first != chess::GameResultReason::NONE)
		return evaluateBoard(board);

	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	if (maximizingPlay) // Maximizing Move
	{
		int maxEval = -100000;
		for (auto move : moves)
		{
			board.makeMove(move);
			int eval = minimax(board, depth - 1, false, alpha, beta);
			board.unmakeMove(move);
			maxEval = std::max(maxEval, eval);
			alpha = std::max(alpha, eval);
			if (beta <= alpha) break;
		}
		return maxEval;
	}
	else // Minimizing Move
	{
		int minEval = 100000;
		for (auto move : moves)
		{
			board.makeMove(move);
			int eval = minimax(board, depth - 1, true, alpha, beta);
			board.unmakeMove(move);
			minEval = std::min(minEval, eval);
			beta = std::min(beta, eval);
			if (beta <= alpha) break;
		}
		return minEval;
	}
}

// Basic Heuristic
// TO DO: Improve heuristic to make the bot smarter
int MinMaxBot::evaluateBoard(const chess::Board& board)
{
	int score = 0;

	// Runs through all squares of the board
	for (auto sq = chess::Square(chess::Square::underlying::SQ_A1); sq < chess::Square(chess::Square::underlying::SQ_H8); sq++)
	{
		auto piece = board.at(sq);
		if (piece == chess::Piece::NONE)
			continue;

		int value = 0;
		switch (piece.type().internal())
		{
		case chess::PieceType::PAWN: value = 100; break;
		case chess::PieceType::KNIGHT: value = 320; break;
		case chess::PieceType::BISHOP: value = 330; break;
		case chess::PieceType::ROOK: value = 500; break;
		case chess::PieceType::QUEEN: value = 900; break;
		case chess::PieceType::KING: value = 20000; break;
		}

		if (piece.color() == chess::Color::WHITE)
			score += value;
		else
			score -= value;
	}
	return(board.sideToMove() == chess::Color::WHITE) ? score : -score; // Score doesn't return what I thought it would, will need to fix
}