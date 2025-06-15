#include "ChessPiece.hpp"

#include "ChessMove.hpp"
#include "PieceBehavior.hpp"

PieceID ChessPiece::getID() { return behavior ? behavior->getID() : NONE; }

std::list<ChessMove> ChessPiece::generateMoves() { return behavior->generateMoves(*this); }
