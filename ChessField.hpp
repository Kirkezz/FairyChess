#ifndef CHESSFIELD_HPP
#define CHESSFIELD_HPP

#include <list>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "ChessFieldNode.hpp"
#include "ChessMove.hpp"
#include "ChessPiece.hpp"
#include "PieceBehavior.hpp"

#include "fwd_decl.h"

class ChessField {
    size_t width, height;
    std::map<PieceID, PieceBehavior *> behavior_cache;
  public:
    size_t getWidth() { return width; }
    size_t getHeight() { return height; }
    size_t size() { return width * height; }
    size_t to1D(int x, int y) { return x + y * width; }
    std::pair<int, int> to2D(size_t i) { return {i % width, i / width}; }

    ChessField();
    ChessField(size_t width, size_t height);

    Node *at(int x, int y);
    Node *at(size_t i);
    ChessPiece *operator()(size_t i);

    PieceBehavior *createBehavior(PieceID id);
    void insertNode(size_t pos, ChessPiecesSetId pieces_id, char piece, PieceTeam team);
    void insertNode(size_t pos, PieceID id, PieceTeam team);

    ChessRules *rules;
    void initRules(ChessRulesID rules_id);

    void generatePossibleMoves();

    std::stack<ChessMove> move_stack;
    void move(const ChessMove &m);
    void unmove();

    bool isUnderAttack(size_t pos);

    ~ChessField();

    ChessField(const ChessField &) = delete;
    ChessField &operator=(const ChessField &) = delete;

    ChessField(ChessField &&) noexcept = default;
    ChessField &operator=(ChessField &&) noexcept = default;

  private:
    friend class Node;
    std::vector<Node *> field;

    std::set<PieceBehavior *> unique_bhvs; // is used in isUnderAttack(), updated in generatePossibleMoves
    std::vector<std::list<ChessMove>> possible_moves;
};

#endif // CHESSFIELD_HPP
