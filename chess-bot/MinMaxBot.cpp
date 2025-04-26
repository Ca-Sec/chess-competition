#include "MinMaxBot.h"
#include <vector>
#include <random>
#include <algorithm>

MinMaxBot::MinMaxBot(int depth)
	: m_depth(depth)
{ }

int MinMaxBot::evaluateMove(const chess::Move& move, const chess::Board& board)
{
	chess::Board tempBoard = board;
	tempBoard.makeMove(move);
	return evaluateBoard(tempBoard);
}

std::string MinMaxBot::getBestMove(const std::string& fen)
{
	chess::Board board(fen);
	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	if (moves.size() == 0)
		return "";

	int bestScore = -100000;
	chess::Move bestMove;

	std::sort(moves.begin(), moves.end(), [&](const chess::Move& move1, const chess::Move& move2) {
		return evaluateMove(move1, board) > evaluateMove(move2, board);
		});

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

int MinMaxBot::minimax(chess::Board& board, int depth, bool maximizingPlay, int alpha, int beta)
{
	if (depth == 0 || board.isGameOver().first != chess::GameResultReason::NONE)
		return 0;

	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	if (maximizingPlay)
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
	else
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

int MinMaxBot::evaluateBoard(const chess::Board& board)
{
	int score = 0;

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
	return(board.sideToMove() == chess::Color::WHITE) ? score : -score;
}