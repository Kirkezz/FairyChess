#ifndef PIECEBEHAVIOR_HPP
#define PIECEBEHAVIOR_HPP

#include <cctype>
#include <inttypes.h>
#include <list>
#include <vector>

#include "fwd_decl.h"

static PieceID toPieceID(ChessPiecesSetId pieces_id, char piece) { return PIECE(pieces_id, std::tolower(piece)); }

class PieceBehavior {
  public:
    void* data = nullptr;
    virtual ~PieceBehavior() = default;
    virtual bool isAsymmetric() { return false; } // is used to determine whether move legality can be optimized
    virtual PieceID getID() { return NONE; };
    virtual std::list<ChessMove> generateMoves(ChessPiece& piece) = 0;
};

#define INFINITE_RIDER (std::numeric_limits<uint16_t>::max())

enum class MoveMode {
    NORMAL,      // Can move on empty squares and capture (rook-like)
    MOVE_ONLY,   // Can move only on empty squares (pawn-forward-move-like)
    CAPTURE_ONLY // Can move only on non-empty squares (pawn-capture-like)
};
struct RiderBehaviorParams {
    unsigned n;
    unsigned m;
    unsigned times;
    std::vector<std::pair<int, int>> mask;
    MoveMode mode = MoveMode::NORMAL;
};

using DirectionalRiderParams = std::vector<RiderBehaviorParams>;

#endif // PIECEBEHAVIOR_HPP
