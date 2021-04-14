cmake_minimum_required(VERSION 3.0)

project(C_minus)

add_library(LexerLib CM_Lexer.cpp CM_Lexer.hpp CM_Signal.cpp CM_Signal.hpp)

add_executable(cscan CMlexertest.cpp)

target_link_libraries(cscan LexerLib)

include_directories(./)