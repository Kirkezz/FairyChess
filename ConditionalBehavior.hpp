#ifndef CONDITIONALBEHAVIOR_HPP
#define CONDITIONALBEHAVIOR_HPP

#include <functional>
#include <memory>

#include "PieceBehavior.hpp"

#include "fwd_decl.h"

class ConditionalBehavior : public PieceBehavior {
  private:
    std::unique_ptr<PieceBehavior> behavior;
    std::function<bool(ChessPiece&)> condition;

  public:
    template<typename Behavior>
    ConditionalBehavior(Behavior&& bhv, std::function<bool(ChessPiece&)> condition) : condition(std::move(condition)) {
        behavior = std::make_unique<std::decay_t<Behavior>>(std::forward<Behavior>(bhv));
    }

    std::list<ChessMove> generateMoves(ChessPiece& piece) override;
};

class FirstMoveBehavior : public ConditionalBehavior {
  public:
    template<typename Behavior>
    FirstMoveBehavior(Behavior&& bhv);
};

#endif // CONDITIONALBEHAVIOR_HPP
