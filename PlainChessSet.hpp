#ifndef PLAINCHESSSET_H
#define PLAINCHESSSET_H

#include "CompositeBehavior.hpp"
#include "RiderBehavior.hpp"

class EnPassantBehavior : public PieceBehavior {
  public:
    std::list<ChessMove> generateMoves(ChessPiece& piece) override;
};

class PromotionBehavior : public PieceBehavior {
  public:
    std::list<ChessMove> generateMoves(ChessPiece& piece) override;
};

// Пешка: Directional non-inclusive (0, +-1) rider
// Combined with First move Conditional(!moves.empty()) Directional non-inclusive (0, +-2) rider
// Combined with CAPTURE_ONLY Directional ((-1, +1), +-1) rider
// Combined with en passant behavior
// Combined with Transform to queen/rook/knight/bishop behavior if on last row
// TODO: Rename symmetric to just rider and add DirectionalRiderBehavior
class PawnBehavior : public CompositeBehavior {
    static const DirectionalRiderParams fw1_rider_params;
    static const DirectionalRiderParams fw2_rider_params;
    static const DirectionalRiderParams capture_params;
  public:
    PawnBehavior();
    PieceID getID() override { return STD_PAWN; }
};

class KnightBehavior : public RiderBehavior {
    static const RiderBehaviorParams params;
  public:
    KnightBehavior() : RiderBehavior(&params) {}
    PieceID getID() override { return STD_KNIGHT; }
};

class BishopBehavior : public RiderBehavior {
    static const RiderBehaviorParams params;
  public:
    BishopBehavior() : RiderBehavior(&params) {}
    PieceID getID() override { return STD_BISHOP; }
};

class RookBehavior : public RiderBehavior {
    static const RiderBehaviorParams params;
  public:
    RookBehavior() : RiderBehavior(&params) {}
    PieceID getID() override { return STD_ROOK; }
};

class QueenBehavior : public CompositeBehavior {
  public:
    QueenBehavior() : CompositeBehavior(RookBehavior(), BishopBehavior()) {}
    PieceID getID() override { return STD_QUEEN; }
};

class CastlingBehavior : public PieceBehavior {
  public:
    CastlingBehavior() {}
    std::list<ChessMove> generateMoves(ChessPiece& piece) override;
    PieceID getID() override { return COMMON_CASTLING; }
};

class KingBehavior : public CompositeBehavior {
    static const RiderBehaviorParams params;
  public:
    KingBehavior() : CompositeBehavior(CastlingBehavior(), RiderBehavior(&params)) {}
    PieceID getID() override { return STD_QUEEN; }
};

#endif // PLAINCHESSSET_H
