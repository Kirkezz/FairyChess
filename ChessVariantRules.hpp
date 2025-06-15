#ifndef CHESSVARIANTRULES_HPP
#define CHESSVARIANTRULES_HPP

#include <list>

#include "fwd_decl.h"

class ChessRules {
    ChessField* board;

    unsigned moves_without_capture_draw = 50;
    unsigned fold_repetition = 3;

    unsigned moves = 0;
    unsigned teamToMove = 0;
  public:
    ChessRules(ChessField* board);
    virtual ChessRulesID getId() = 0;
    virtual void verifyMoves(std::list<ChessMove>& moves) = 0;
    virtual void handleMove(ChessMove* move) = 0;
    virtual void handleUnmove(ChessMove* move) = 0;
    virtual int getGameState() = 0;
};

class StandardChessRules : public ChessRules {
    size_t white_king_pos, black_king_pos;
  public:
    bool a_castling[2] = {true, true}, h_castling[2] = {true, true};
    StandardChessRules(ChessField* board) : ChessRules(board) {}
    ChessRulesID getId() { return R_STANDARD_CHESS; }
    void verifyMoves(std::list<ChessMove>& moves);
    void handleMove(ChessMove* move);
    void handleUnmove(ChessMove* move);
    int getGameState() { return 0; }
};

#endif // CHESSVARIANTRULES_HPP
