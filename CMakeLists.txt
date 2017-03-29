cmake_minimum_required(VERSION 3.6)
project(Othello)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Pawn.h Board.cpp Board.h Header.h Pawn.cpp Player.cpp Player.h)
add_executable(Othello ${SOURCE_FILES})