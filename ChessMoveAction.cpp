#include "ChessMoveAction.hpp"

#include <utility>

#include "ChessField.hpp"
#include "ChessFieldNode.hpp"
#include "ChessMove.hpp"
#include "ChessPiece.hpp"

void RemoveActionSE::apply(ChessMove &m) { removed = std::move(node->piece); }

void RemoveActionSE::undo(ChessMove &m) { node->piece = std::move(removed); }

void CaptureAction::apply(ChessMove &m) {
    captured = std::move(m.to->piece);
    m.to->setPiece(std::move(m.from->piece));
}

void CaptureAction::undo(ChessMove &m) {
    m.from->setPiece(std::move(m.to->piece));
    m.to->setPiece(std::move(captured));
}

void CaptureActionSE::apply(ChessMove &m) {
    captured = std::move(to->piece);
    to->setPiece(std::move(from->piece));
}

void CaptureActionSE::undo(ChessMove &m) {
    from->setPiece(std::move(to->piece));
    to->setPiece(std::move(captured));
}

void TransformActionSE::apply(ChessMove &m) { prev_behavior = std::exchange(node->piece->behavior, node->board->createBehavior(to_id)); }

void TransformActionSE::undo(ChessMove &m) {
    node->piece->behavior = prev_behavior;
    prev_behavior = nullptr;
}

void CustomActionSE::apply(ChessMove &m) { custom_apply(m); }

void CustomActionSE::undo(ChessMove &m) { custom_undo(m); }
