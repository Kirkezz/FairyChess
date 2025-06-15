#ifndef DIRECTIONALRIDERBEHAVIOR_HPP
#define DIRECTIONALRIDERBEHAVIOR_HPP

#include <limits>
#include <vector>

#include "PieceBehavior.hpp"

class DirectionalRiderBehavior : public PieceBehavior {
    const std::vector<RiderBehaviorParams>* params;
  public:
    DirectionalRiderBehavior(const std::vector<RiderBehaviorParams>* params) : params(params) {}

    std::list<ChessMove> generateMoves(ChessPiece& piece) override;

    PieceID getID() override { return COMMON_DIRECTIONAL_RIDER; }
};

#endif // DIRECTIONALRIDERBEHAVIOR_HPP
