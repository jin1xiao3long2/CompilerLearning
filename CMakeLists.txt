cmake_minimum_required(VERSION 3.0)

project(compiler_learn)

add_executable(Lexer lexer.hpp lexer.cpp)
add_executable(LexerTest lexertest.cpp)
add_executable(Parser parser.hpp parser.cpp)

add_executable(compilerstest compilerStest.cpp compilerStest.hpp)


add_library(LibLexer lexer.hpp lexer.cpp)
add_executable(SimpleParser simpleParser.cpp simpleParser.hpp)
#target_link_libraries(SimpleParser LibLexer)
add_library(LibParser simpleParser.cpp simpleParser.hpp)
add_executable(ParserTest simpleParsertest.cpp)
add_executable(repotest testrepo.cpp)
target_link_libraries(ParserTest LibParser LibLexer)
include_directories(Compiler)
add_subdirectory(Experience)