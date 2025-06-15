#ifndef CHESSPIECE_HPP
#define CHESSPIECE_HPP

#include <list>

#include "PieceBehavior.hpp"
#include "fwd_decl.h"

struct ChessPiece {
    Node* node;

    PieceID getID();
    PieceBehavior* behavior;
    PieceTeam team;
    uint16_t moves_N = 0;

    std::list<ChessMove> generateMoves();
};

#endif // CHESSPIECE_HPP
