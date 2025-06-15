#ifndef CHESSMOVEACTION_HPP
#define CHESSMOVEACTION_HPP

#include <functional>
#include <memory>

#include "fwd_decl.h"

#include "ChessPiece.hpp"

struct Action {
    virtual ~Action() = default;
    virtual void apply(ChessMove& m) = 0;
    virtual void undo(ChessMove& m) = 0;
    virtual Action* clone() const = 0;
};

// SE - SideEffect
struct RemoveActionSE : public Action {
    std::unique_ptr<ChessPiece> removed;
    Node* node;

    RemoveActionSE(Node* node) : node(node) {}

    RemoveActionSE(const RemoveActionSE& a) {
        if (a.removed) removed.reset(new ChessPiece(*a.removed));
    }
    RemoveActionSE& operator=(const RemoveActionSE&) = delete;

    RemoveActionSE(RemoveActionSE&&) noexcept = default;
    RemoveActionSE& operator=(RemoveActionSE&&) noexcept = default;

    void apply(ChessMove& m);
    void undo(ChessMove& m);
    virtual RemoveActionSE* clone() const { return new RemoveActionSE(*this); }
};

struct CaptureAction : public Action {
    std::unique_ptr<ChessPiece> captured;

    CaptureAction() = default;

    CaptureAction(const CaptureAction& a) {
        if (a.captured) captured.reset(new ChessPiece(*a.captured));
    }
    CaptureAction& operator=(const CaptureAction&) = delete;

    CaptureAction(CaptureAction&&) noexcept = default;
    CaptureAction& operator=(CaptureAction&&) noexcept = default;

    void apply(ChessMove& m);
    void undo(ChessMove& m);
    virtual CaptureAction* clone() const { return new CaptureAction(*this); }
};

struct CaptureActionSE : public Action {
    std::unique_ptr<ChessPiece> captured;
    Node *from, *to;

    CaptureActionSE(Node* from, Node* to) : from(from), to(to) {}

    CaptureActionSE(const CaptureActionSE& a) {
        if (a.captured) captured.reset(new ChessPiece(*a.captured));
    }
    CaptureActionSE& operator=(const CaptureActionSE&) = delete;

    CaptureActionSE(CaptureActionSE&&) noexcept = default;
    CaptureActionSE& operator=(CaptureActionSE&&) noexcept = default;

    void apply(ChessMove& m);
    void undo(ChessMove& m);
    virtual CaptureActionSE* clone() const { return new CaptureActionSE(*this); }
};

struct TransformActionSE : public Action {
    Node* node;
    PieceID to_id;
    PieceBehavior* prev_behavior;

    TransformActionSE(Node* node, PieceID to_id) : node(node), to_id(to_id) {}

    void apply(ChessMove& m);
    void undo(ChessMove& m);
    virtual TransformActionSE* clone() const { return new TransformActionSE(*this); }
};

// usecase: overly specific actions
struct CustomActionSE : public Action {
    std::function<void(ChessMove& m)> custom_apply, custom_undo;
    CustomActionSE(std::function<void(ChessMove& m)> custom_apply, std::function<void(ChessMove& m)> custom_undo)
        : custom_apply(std::move(custom_apply)), custom_undo(std::move(custom_undo)) {}

    void apply(ChessMove& m);
    void undo(ChessMove& m);
    virtual CustomActionSE* clone() const { return new CustomActionSE(*this); }
};

#endif // CHESSMOVEACTION_HPP
