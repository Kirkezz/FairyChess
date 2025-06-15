#include "ChessField.hpp"

#include "ChessPiece.hpp"
#include "ChessVariantRules.hpp"
#include "PlainChessSet.hpp"

#include <iostream>

using namespace std;

ChessField::ChessField() {}

ChessField::ChessField(size_t width, size_t height) : width(width), height(height) {
    field = vector<Node *>(width * height, nullptr);

    if (behavior_cache.empty()) {
        behavior_cache[PieceID::STD_PAWN] = new PawnBehavior;
        behavior_cache[PieceID::STD_KNIGHT] = new KnightBehavior;
        behavior_cache[PieceID::STD_BISHOP] = new BishopBehavior;
        behavior_cache[PieceID::STD_ROOK] = new RookBehavior;
        behavior_cache[PieceID::STD_QUEEN] = new QueenBehavior;
        behavior_cache[PieceID::STD_KING] = new KingBehavior;
    }
}

Node *ChessField::at(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
    return at(to1D(x, y));
}
Node *ChessField::at(size_t i) { return field[i]; }

ChessPiece *ChessField::operator()(size_t i) {
    if (field[i]) return field[i]->piece.get();
    return nullptr;
}

PieceBehavior* ChessField::createBehavior(PieceID id) {
    switch (id) {
    default: return behavior_cache[id];
    }
}

void ChessField::insertNode(size_t pos, ChessPiecesSetId pieces_id, char piece, PieceTeam team) { insertNode(pos, toPieceID(pieces_id, piece), team); }

void ChessField::insertNode(size_t pos, PieceID id, PieceTeam team) {
    field[pos] = new Node;
    field[pos]->board = this;
    field[pos]->pos = pos;
    if (id != NONE) field[pos]->piece = make_unique<ChessPiece>(field[pos], createBehavior(id), team);
}

void ChessField::initRules(ChessRulesID rules_id) {
    switch (rules_id) {
    case R_STANDARD_CHESS: rules = new StandardChessRules(this); break;
    }
}

void ChessField::generatePossibleMoves() {
    //if (pm_relevance == current_move) return;

    possible_moves.clear();
    unique_bhvs.clear();
    possible_moves.resize(field.size());
    for (size_t i = 0; i < field.size(); ++i) {
        if (field[i] && field[i]->piece) {
            possible_moves[i] = field[i]->piece->generateMoves();
            unique_bhvs.insert(field[i]->piece->behavior);
        }
        //verifyMoves(possible_moves[i]);
    }

    //pm_relevance = current_move;

    for (auto &i : possible_moves) {
        if (!i.empty()) {
            std::cout << i.begin()->from->pos << ": " << i.size() << "( ";
            for (auto &j : i)
                std::cout << j.to->pos << " ";
            std::cout << "); ";
        }
    }
    std::cout << std::endl;
}

void ChessField::move(const ChessMove &m) {
    move_stack.push(m);
    for (auto &i : move_stack.top().actions) {
        i->apply(move_stack.top());
    }
    rules->handleMove(&move_stack.top());
}

void ChessField::unmove() {
    for (auto &i : move_stack.top().actions) {
        i->undo(move_stack.top());
    }
    rules->handleUnmove(&move_stack.top());
    move_stack.pop();
}

bool ChessField::isUnderAttack(size_t pos) {
    generatePossibleMoves();
    vector<PieceBehavior *> unique_bhvs;
    for (auto &i : possible_moves)
        for (auto &j : i)
            if (j.to->pos == pos) return true;
    return false;
}

ChessField::~ChessField() {
    for (auto i : field)
        if (i) delete i;
}
