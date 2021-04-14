cmake_minimum_required(VERSION 3.0)

project(Tiny)

add_library(tinyLexer Tiny_Lexer.cpp Tiny_Lexer.hpp Tiny_Signal.cpp Tiny_Signal.hpp)
add_library(tinyParser Tiny_Nodes.hpp Tiny_Nodes.cpp Tiny_Parser.cpp Tiny_Parser.hpp)

add_executable(tinyscan tinylexerMain.cpp)
add_executable(tiny tinyparserMain.cpp)

target_link_libraries(tinyscan tinyLexer)
target_link_libraries(tiny tinyParser tinyLexer)
include_directories(./)