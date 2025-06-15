#ifndef FWD_DECL_H
#define FWD_DECL_H

#include <inttypes.h>

struct Node;
struct ChessMove;
class ChessField;
class ChessPiece;
class PieceBehavior;
class ChessRules;

enum ChessPiecesSetId { STANDARD_CHESS = 1, COMMON = 26625 }; // is needed to match the PieceID to the corresponding FEN character
enum ChessRulesID { R_STANDARD_CHESS = 1 };
#define PIECE(variant, c) (PieceID)(variant + c - 'a')
enum PieceID : uint16_t {
    NONE = 0,
    STD_PAWN = PIECE(STANDARD_CHESS, 'p'),
    STD_KNIGHT = PIECE(STANDARD_CHESS, 'n'),
    STD_BISHOP = PIECE(STANDARD_CHESS, 'b'),
    STD_ROOK = PIECE(STANDARD_CHESS, 'r'),
    STD_QUEEN = PIECE(STANDARD_CHESS, 'q'),
    STD_KING = PIECE(STANDARD_CHESS, 'k'),
    COMMON_RIDER = COMMON + 1,
    COMMON_DIRECTIONAL_RIDER = COMMON + 2,
    COMMON_CASTLING = COMMON + 3
};
enum PieceTeam : int8_t { NEUTRAL = -1, WHITE = 0, BLACK = 1 };

#endif // FWD_DECL_H
