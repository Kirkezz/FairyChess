#ifndef CHESSFIELDNODE_HPP
#define CHESSFIELDNODE_HPP

#include <array>
#include <cstddef>
#include <memory>
#include <optional>

#include "fwd_decl.h"

enum Direction : uint8_t { UP, DOWN, RIGHT, LEFT, DIRECTIONS_N };
struct Node {
    ChessField *board;
    std::size_t pos;

    std::unique_ptr<ChessPiece> piece;
    void setPiece(std::unique_ptr<ChessPiece> new_piece);

    std::optional<size_t> offset(size_t dir, int times = 1, size_t i = -1) const {
        // (↑ ↓ → ←) ☦
        static constexpr std::array wallArr = {&Node::wallU, &Node::wallD, &Node::wallR, &Node::wallL};
        static constexpr std::array offsetArr = {&Node::offsetU, &Node::offsetD, &Node::offsetR, &Node::offsetL};
        if (times < 0) { return offset((dir % 2) ? (dir - 1) : (dir + 1), -times, i); }
        std::optional<size_t> result = ((i == -1) ? this->pos : i);
        while (times-- && result) {
            result = !(this->*wallArr[dir])(*result) ? std::optional((this->*offsetArr[dir])(*result)) : std::nullopt;
        }
        return result;
    }
    size_t offsetU(size_t i) const;
    size_t offsetD(size_t i) const;
    size_t offsetR(size_t i) const;
    size_t offsetL(size_t i) const;
    bool wallU(size_t i) const;
    bool wallD(size_t i) const;
    bool wallR(size_t i) const;
    bool wallL(size_t i) const;
    int x() const;
    int y() const;
};

#endif // CHESSFIELDNODE_HPP
