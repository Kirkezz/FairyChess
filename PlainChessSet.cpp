#include "PlainChessSet.hpp"

#include "ChessField.hpp"
#include "ChessFieldNode.hpp"
#include "ChessMove.hpp"
#include "ChessPiece.hpp"
#include "ChessVariantRules.hpp"
#include "ConditionalBehavior.hpp"
#include "DirectionalRiderBehavior.hpp"

const DirectionalRiderParams PawnBehavior::fw1_rider_params = {{1, 1, 1, {{{0, -1}}}, MoveMode::MOVE_ONLY}, {1, 1, 1, {{{0, 1}}}, MoveMode::MOVE_ONLY}};
const DirectionalRiderParams PawnBehavior::fw2_rider_params = {{1, 1, 1, {{{0, -2}}}, MoveMode::MOVE_ONLY}, {1, 1, 1, {{{0, 2}}}, MoveMode::MOVE_ONLY}};
const DirectionalRiderParams PawnBehavior::capture_params = {{1, 1, 1, {{1, -1}, {-1, -1}}, MoveMode::CAPTURE_ONLY},
                                                             {1, 1, 1, {{1, 1}, {-1, 1}}, MoveMode::CAPTURE_ONLY}};
const RiderBehaviorParams KnightBehavior::params = {1, 2, 1, {{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}};
const RiderBehaviorParams BishopBehavior::params = {1, 1, INFINITE_RIDER, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};
const RiderBehaviorParams RookBehavior::params = {1, 1, INFINITE_RIDER, {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
const RiderBehaviorParams KingBehavior::params = {1, 1, 1, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

std::list<ChessMove> EnPassantBehavior::generateMoves(ChessPiece &piece) {
    auto &board = *piece.node->board;
    std::list<ChessMove> moves;

    if (piece.team == WHITE && piece.node->y() == 3) {
        for (auto i : {LEFT, RIGHT}) {
            if (auto offset = piece.node->offset(i); offset) {
                if (ChessPiece *offset_p = board(*offset); offset_p && offset_p->moves_N == 1 && offset_p->getID() == STD_PAWN && offset_p->team != piece.team
                                                           && board.move_stack.top().to->pos == *offset) {
                    auto to = offset_p->node->offset(piece.team == WHITE ? UP : DOWN);
                    moves.emplace_back(piece.node, board.at(*to), CaptureAction(), RemoveActionSE(board.at(*offset)));
                }
            }
        }
    }

    return moves;
}

std::list<ChessMove> PromotionBehavior::generateMoves(ChessPiece &piece) {
    std::list<ChessMove> &moves = *((std::list<ChessMove> *) piece.behavior->data);
    auto board = piece.node->board;

    for (auto it = moves.begin(); it != moves.end(); ++it) {
        if ((piece.team == WHITE && it->to->y() == 0) || (piece.team == BLACK && it->to->y() == board->getHeight() - 1)) {
            for (auto id : {STD_KNIGHT, STD_BISHOP, STD_ROOK, STD_QUEEN}) {
                moves.push_front(*it);
                moves.front().addActions(TransformActionSE(moves.front().to, id));
            }
            it = moves.erase(it);
            if (it == moves.end()) break;
        }
    }

    return {};
}

PawnBehavior::PawnBehavior()
    : CompositeBehavior(DirectionalRiderBehavior(&fw1_rider_params),
                        ConditionalBehavior(DirectionalRiderBehavior(&fw2_rider_params),
                                            [](ChessPiece &piece) { return !((std::list<ChessMove> *) piece.behavior->data)->empty(); }),
                        DirectionalRiderBehavior(&capture_params), EnPassantBehavior(), PromotionBehavior()) {}

std::list<ChessMove> CastlingBehavior::generateMoves(ChessPiece &piece) {
    ChessField &board = *piece.node->board;
    StandardChessRules *rules = dynamic_cast<StandardChessRules *>(board.rules);
    if (!rules) return {};

    if (!rules->a_castling[piece.team] && !rules->h_castling[piece.team]) return {}; // castling is allowed check

    if (piece.moves_N != 0) { goto irreparable; } // king didn't move check // TODO: move to rules.processMove()

    {
        std::list<ChessMove> moves;
        Node *a_king_to = board.at(2, piece.node->y()), *h_king_to = board.at(6, piece.node->y()); // king -> c/g
        Node *a_rook_to = !a_king_to ? nullptr : board.at(*a_king_to->offset(RIGHT));              // rook -> d
        Node *h_rook_to = !h_king_to ? nullptr : board.at(*h_king_to->offset(LEFT));               // rook -> f

        auto checkSide = [&](Direction dir, Node *king_to, Node *rook_to) {
            if (!king_to || !rook_to) goto irreparable_single;
            if (king_to->piece && king_to->pos != piece.node->pos) return; // king's target square (king_to) is not occupied check

            {
                // Searching for a target rook.
                std::optional<size_t> rook = board.at(piece.node->pos)->offset(dir);
                while (rook) {
                    if (auto i_piece = board(*rook); i_piece) {
                        if (i_piece->getID() == STD_ROOK) { // rook found successfully
                            break;
                        } else {
                            return; // square between king and rook is not occupied check failed
                        }
                    }

                    rook = board.at(*rook)->offset(dir);
                }
                if (!rook) return;
                Node *rook_from = board.at(*rook);

                if (board(*rook)->moves_N != 0) { // target rook didn't move check
                    goto irreparable_single;
                }
                if (rook_to->piece && rook_to->pos != rook_from->pos) return; // target rook's target square is not occupied check

                // Filling an array of cells that will be checked to make sure they are not under attack (except for the king's target square, which is already being checked.)
                std::vector<Node *> under_attack_validate_query;
                for (int x = std::min(king_to->x(), piece.node->x()); x <= std::max(king_to->x(), piece.node->x()); ++x) {
                    Node *node = board.at(board.to1D(x, piece.node->y()));
                    if (node->pos != king_to->pos) {
                        if (node->piece && node->pos != rook_from->pos && node->pos != piece.node->pos) return;
                        under_attack_validate_query.push_back(node);
                    }
                }

                ChessMove move(piece.node, king_to);
                if (piece.node->pos != king_to->pos) move.addActions(CaptureAction());
                if (rook_from->pos != rook_to->pos) move.addActions(CaptureActionSE(rook_from, rook_to));
                bool &castling_flag = (dir == LEFT ? rules->a_castling : rules->h_castling)[piece.team];
                move.addActions(CustomActionSE([&castling_flag](ChessMove &m) { castling_flag = false; }, [&castling_flag](ChessMove &m) { castling_flag = true; }));
                move.under_attack_validate_query = std::move(under_attack_validate_query);
                moves.emplace_back(std::move(move));
            }

        irreparable_single:
            (dir == LEFT ? rules->a_castling : rules->h_castling)[piece.team] = false;
        };

        checkSide(LEFT, a_king_to, a_rook_to);
        checkSide(RIGHT, h_king_to, h_rook_to);

        return moves;
    }

irreparable:
    rules->a_castling[piece.team] = false;
    rules->h_castling[piece.team] = false;
    return {};
}
