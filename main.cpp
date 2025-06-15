#include "FairyChess.hpp"
using namespace std;

#include <array>
#include <iostream>

int main() {
    FairyChess board;

    while (true) {
        string str;
        getline(cin, str);
        board.uciCmd(str);
    }

    // string str = "rnbqkbnr/pppppppp/+8/+8/+8/+8/PPPPPPPP/RNBQKBNR b KQkq"; // startpos
    // string str = "rnbqkbnr/pppppppp/+8/+3P+4/+3p+4/+8/PPPPPPPP/RNBQKBNR"; // en passant
    //string str = "r+3k+2r/+8/+8/+8/+8/+8/+8/R+3K+2R"; // castling
    // string str = "R+6R/+3Q+4/+1Q+4Q+1/+4Q+3/+2Q+4Q/Q+4Q+2/pp+1Q+4/kBNN+1KB+1"; // max moves in one position
    // string str = "r+3k+2r/p+1ppqpb+1/bn+2pnp+1/+3PN+3/+1p+2P+3/+2N+2Q+1p/PPPBBPPP/R+3K+2R w KQkq -";
    // string str = "KP+4pk/+1P+4p+1/+1P+4p+1/+1P+4p+1/+1P+4p+1/+1P+4p+1/+1P+4p+1/+1P+4p+1"; // rotated board
    // string str = "r+3k+2r/p+1ppqpb+1/bn+2pnp+1/+3PN+3/+1p+2P+3/+2N+2Q+1p/PPPBBPPP/R+3K+2R w KQkq - 0 1"; // promotions
    // string str = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"; // kiwipete
    //FairyChess board(STANDARD_CHESS, R_STANDARD_CHESS, str);
    //board.test();
    //while (1) {
    //    board.TEMPprintBoard();
    //    auto _2 = chrono::system_clock::now();
    //    board.generatePossibleMoves();
    //    cout << chrono::system_clock::now() - _2 << endl;
    //    int a, b;
    //    //board.makeRandomMove();
    //    cin >> a >> b;
    //    board.move(a, b);
    //}
}
