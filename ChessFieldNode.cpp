#include "ChessFieldNode.hpp"

#include "ChessField.hpp"
#include "ChessPiece.hpp"

void Node::setPiece(std::unique_ptr<ChessPiece> new_piece) {
    piece = std::move(new_piece);
    piece->node = this;
}

size_t Node::offsetU(size_t i) const { return i - board->width; }
size_t Node::offsetD(size_t i) const { return i + board->width; }
size_t Node::offsetR(size_t i) const { return i + 1; }
size_t Node::offsetL(size_t i) const { return i - 1; }
bool Node::wallU(size_t i) const { return i < board->width || board->height == 1; }
bool Node::wallD(size_t i) const { return i > board->size() - board->width - 1 || board->height == 1; }
bool Node::wallR(size_t i) const { return i % board->width == board->width - 1; }
bool Node::wallL(size_t i) const { return i % board->width == 0; }
int Node::x() const { return pos % board->width; }
int Node::y() const { return pos / board->width; }
