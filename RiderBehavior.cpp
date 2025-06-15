#include "RiderBehavior.hpp"

#include "ChessField.hpp"
#include "ChessMove.hpp"
#include "ChessMoveAction.hpp"

#include <algorithm>

using namespace std;

list<ChessMove> RiderBehavior::generateMoves(ChessPiece &piece) {
    list<ChessMove> result;

    auto [n, m, times, mask, mode] = *params;
    for (unsigned c = 0; c <= (n != m) /* && symmetric */; swap(n, m), ++c) {
        for (const auto &[dx, dy] : mask) {
            optional<size_t> offset = piece.node->pos;
            for (unsigned j = 1; j <= times; ++j) {
                if (offset = piece.node->offset(RIGHT, dx * n, *offset); offset) {
                    if (offset = piece.node->offset(DOWN, dy * m, *offset); offset) {
                        auto to = piece.node->board->at(*offset);
                        if (!to) break;
                        if (to->piece) {
                            if (to->piece->team != piece.team && (mode == MoveMode::NORMAL || mode == MoveMode::CAPTURE_ONLY)) {
                                result.emplace_back(piece.node, to, CaptureAction());
                            }
                            break;
                        } else {
                            if (mode != MoveMode::CAPTURE_ONLY) { result.emplace_back(piece.node, to, CaptureAction()); }
                        }
                    } else
                        break;
                } else
                    break;
            }
        }
    }

    return result;
}
