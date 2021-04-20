cmake_minimum_required(VERSION 3.0)

project(C_minus)

add_library(LexerLib CM_Lexer.cpp CM_Lexer.hpp CM_Signal.cpp CM_Signal.hpp)
add_library(ParserLib CM_Nodes.hpp CM_Nodes.cpp CM_Parser.hpp CM_Parser.cpp)

add_executable(cscan CMlexertest.cpp)
add_executable(cminus CMParserMain.cpp)

target_link_libraries(cscan LexerLib)
target_link_libraries(cminus LexerLib ParserLib)

include_directories(./)