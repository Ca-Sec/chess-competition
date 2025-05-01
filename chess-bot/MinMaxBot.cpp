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
	m_transpositionTable.clear();

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
	uint64_t hash = board.zobrist();

	auto it = m_transpositionTable.find(hash);
	if (it != m_transpositionTable.end())
	{
		TTEntry& entry = it->second;
		if (entry.depth >= depth)
		{
			if (entry.type == NodeType::EXACT)
				return entry.score;
			else if (entry.type == NodeType::LOWER && entry.score > alpha)
				alpha = entry.score;
			else if (entry.type == NodeType::UPPER && entry.score < beta)
				beta = entry.score;

			if (alpha >= beta)
				return entry.score;
		}
	}

	if (depth == 0 || board.isGameOver().first != chess::GameResultReason::NONE)
		return evaluateBoard(board);

	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	int bestScore = maximizingPlay ? -100000 : 100000;

	for (auto move : moves)
	{
		board.makeMove(move);
		int eval = minimax(board, depth - 1, !maximizingPlay, alpha, beta);
		board.unmakeMove(move);

		if (maximizingPlay) {
			bestScore = std::max(bestScore, eval);
			alpha = std::max(alpha, eval);
		}
		else {
			bestScore = std::min(bestScore, eval);
			beta = std::min(beta, eval);
		}

		if (beta <= alpha) break;
	}

	NodeType type;
	if (bestScore <= alpha) type = NodeType::UPPER;
	else if (bestScore >= beta) type = NodeType::LOWER;
	else type = NodeType::EXACT;

	m_transpositionTable[hash] = { bestScore, depth, type };
	return bestScore;
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