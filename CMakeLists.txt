cmake_minimum_required(VERSION 3.16)

project(FairyChess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FairyChess main.cpp
    FairyChess.hpp FairyChess.cpp
    ChessField.hpp ChessField.cpp
    ChessFieldNode.hpp ChessFieldNode.cpp
    ChessPiece.hpp ChessPiece.cpp
    ChessMove.hpp ChessMove.cpp
    ChessMoveAction.hpp ChessMoveAction.cpp
    fwd_decl.h
    PlainChessSet.hpp PlainChessSet.cpp
    RiderBehavior.hpp RiderBehavior.cpp
    PieceBehavior.hpp PieceBehavior.cpp
    CompositeBehavior.hpp CompositeBehavior.cpp
    ChessVariantRules.hpp ChessVariantRules.cpp
    DirectionalRiderBehavior.hpp DirectionalRiderBehavior.cpp
    ConditionalBehavior.hpp ConditionalBehavior.cpp)

include(GNUInstallDirs)
install(TARGETS FairyChess
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
