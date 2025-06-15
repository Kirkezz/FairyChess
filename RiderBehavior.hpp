#ifndef RIDERBEHAVIOR_HPP
#define RIDERBEHAVIOR_HPP

#include <limits>
#include <vector>

#include "PieceBehavior.hpp"

class RiderBehavior : public PieceBehavior {
    const RiderBehaviorParams* params;
  public:
    RiderBehavior(const RiderBehaviorParams* params) : params(params) {}

    std::list<ChessMove> generateMoves(ChessPiece& piece) override;

    PieceID getID() override { return COMMON_RIDER; }
};

#endif // RIDERBEHAVIOR_HPP
