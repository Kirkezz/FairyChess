#ifndef FAIRYCHESS_HPP
#define FAIRYCHESS_HPP

#include "ChessField.hpp"
#include <sstream>
#include <string>
#include <variant>

using namespace std;

class FairyChess {
  public:
    FairyChess();
    FairyChess(ChessPiecesSetId pieces_id, ChessRulesID rules_id, std::string FEN) {
        unsigned width = 0, current_width = 0, height = 1, nodes = 0;
        bool sign;
        string buffer;

        vector<variant<int, char>> parsed;
        for (size_t i = 0; i < FEN.length(); ++i) {
            if (FEN[i] == '-' || FEN[i] == '+') {
                sign = (FEN[i++] == '-');

                while (isdigit(FEN[i]))
                    buffer += FEN[i++];

                int gap = stoi(buffer);
                current_width += gap;

                parsed.push_back((int) ((sign ? -1 : 1) * gap));
                buffer.clear();
                --i;
                continue;
            }

            if (FEN[i] == '/') {
                ++height;
                width = max(width, current_width);
                current_width = 0;
                parsed.push_back(0);
            } else {
                ++current_width;
                parsed.push_back((char) FEN[i]);
            }
        }
        width = max(width, current_width);

        board = ChessField(width, height);

        int pos = 0;
        for (auto i : parsed) {
            if (i.index() == 0) {
                int gap = get<int>(i);
                if (gap == 0) {
                    --pos;
                    pos = (pos / width + 1) * width; // round up to next line
                } else if (gap < 0) {
                    pos += -gap;
                } else {
                    while (gap--) {
                        board.insertNode(pos++, NONE, NEUTRAL);
                    }
                }
            } else {
                char c = get<char>(i);
                board.insertNode(pos++, toPieceID(pieces_id, c), (c >= 'a' && c <= 'z') ? BLACK : WHITE);
            }
        }

        board.initRules(R_STANDARD_CHESS);
    }

    void test() {
        board.generatePossibleMoves();
    }

    typedef void (FairyChess::*uci_cmd_handler_t)(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
    std::map<string, uci_cmd_handler_t> m = {{"uci", &FairyChess::uci}};
    void uciCmd(std::string str) {
        auto words = split(str);
        for (auto i : words) {}
    }

  private:
    ChessField board;

    std::vector<std::string> split(const std::string& str) {
        std::vector<std::string> tokens;
        std::istringstream iss(str);
        std::string token;

        while (iss >> token) {
            tokens.push_back(token);
        }

        return tokens;
    }

    void uci(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end) {}
};

#endif // FAIRYCHESS_HPP
