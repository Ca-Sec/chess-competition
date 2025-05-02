#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include "chess.hpp"

enum class NodeType { EXACT, LOWER, UPPER };

struct TTEntry {
	int score;
	int depth;
	NodeType type;
};

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
	std::unordered_map<uint64_t, TTEntry> m_transpositionTable;

	std::chrono::steady_clock::time_point m_startTime;
	int m_timeLimitMillis = 9000;
};