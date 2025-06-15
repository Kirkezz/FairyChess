#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <vector>

#include "ChessMoveAction.hpp"

struct ChessMove {
    ChessMove(const ChessMove &m);

    Node *from, *to;
    std::vector<std::unique_ptr<Action>> actions;
    std::vector<Node *> under_attack_validate_query;

    template<typename... Actions>
    ChessMove(Node *from, Node *to, Actions &&...acns) : from(from), to(to) {
        addActions(std::forward<Actions>(acns)...);
    }

    template<typename... Actions>
    void addActions(Actions &&...acns) {
        actions.reserve(actions.size() + sizeof...(acns));
        (actions.push_back(std::make_unique<std::decay_t<Actions>>(std::forward<Actions>(acns))), ...);
    }
};

#endif // CHESSMOVE_H
