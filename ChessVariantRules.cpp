#include "ChessVariantRules.hpp"

#include "ChessField.hpp"
#include "ChessFieldNode.hpp"
#include "ChessMove.hpp"
#include "ChessPiece.hpp"
#include "PlainChessSet.hpp"

ChessRules::ChessRules(ChessField* board) : board(board) {}

void StandardChessRules::verifyMoves(std::list<ChessMove> &moves) {}

void StandardChessRules::handleMove(ChessMove *move) {
    if (move->from->piece->getID() == STD_KING) {
        if (move->from->piece->team == WHITE) white_king_pos = move->from->pos;
        if (move->from->piece->team == WHITE) black_king_pos = move->from->pos;
    }
}

void StandardChessRules::handleUnmove(ChessMove *move) {
    std::swap(move->from, move->to);
    handleMove(move);
    std::swap(move->from, move->to);
}
