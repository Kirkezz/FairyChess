#ifndef COMPOSITEBEHAVIOR_HPP
#define COMPOSITEBEHAVIOR_HPP

#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "PieceBehavior.hpp"

class CompositeBehavior : public PieceBehavior {
  private:
    std::vector<std::unique_ptr<PieceBehavior>> behaviors;

  public:
    template<typename... Behaviors>
    CompositeBehavior(Behaviors&&... bhvs) {
        behaviors.reserve(sizeof...(bhvs));
        (behaviors.push_back(std::make_unique<std::decay_t<Behaviors>>(std::forward<Behaviors>(bhvs))), ...);
    }
    std::list<ChessMove> generateMoves(ChessPiece& piece) override;
};

#endif // COMPOSITEBEHAVIOR_HPP
