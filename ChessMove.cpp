#include "ChessMove.hpp"

ChessMove::ChessMove(const ChessMove &m) {
    from = m.from;
    to = m.to;

    actions.resize(m.actions.size());
    for (size_t i = 0; i < m.actions.size(); ++i) {
        actions[i].reset(m.actions[i]->clone());
    }
}
