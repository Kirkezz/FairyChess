#include "CompositeBehavior.hpp"

#include "ChessMove.hpp"

std::list<ChessMove> CompositeBehavior::generateMoves(ChessPiece &piece) {
    if (piece.behavior != this) exit(42);
    std::list<ChessMove> all_moves;

    data = (void *) &all_moves;
    for (const auto &behavior : behaviors) {
        std::list<ChessMove> moves = behavior->generateMoves(piece);
        all_moves.splice(all_moves.end(), moves);
    }
    data = nullptr;

    return all_moves;
}
