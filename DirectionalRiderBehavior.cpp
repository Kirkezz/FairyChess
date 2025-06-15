#include "DirectionalRiderBehavior.hpp"

#include "ChessMove.hpp"
#include "RiderBehavior.hpp"

std::list<ChessMove> DirectionalRiderBehavior::generateMoves(ChessPiece &piece) {
    std::list<ChessMove> all_moves;

    RiderBehavior rider(&(*params)[piece.team]);
    std::list<ChessMove> moves = rider.generateMoves(piece);
    all_moves.splice(all_moves.end(), moves);

    return all_moves;
}
