#include "ConditionalBehavior.hpp"

#include "ChessMove.hpp"
#include "ChessPiece.hpp"

std::list<ChessMove> ConditionalBehavior::generateMoves(ChessPiece &piece) {
    if (condition(piece)) { return behavior->generateMoves(piece); }
    return {};
}

template<typename Behavior>
FirstMoveBehavior::FirstMoveBehavior(Behavior &&bhv) : ConditionalBehavior(std::forward(bhv), [](ChessPiece &piece) { return piece.moves_N == 0; }) {}
