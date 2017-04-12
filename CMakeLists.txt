cmake_minimum_required(VERSION 3.6)
project(Othello)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Pawn.h Board.cpp Board.h Header.h Pawn.cpp Player.cpp Player.h Game.cpp Game.h Node.cpp Node.h)
add_executable(Othello ${SOURCE_FILES})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Othello ${SFML_LIBRARIES})
endif()
