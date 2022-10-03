cmake_minimum_required(VERSION 3.23)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_1 main.cpp Parser.h Parser.cpp ColonAutomaton.cpp ColonDashAutomaton.cpp Lexer.cpp Token.cpp CommaAutomaton.h CommaAutomaton.cpp PeriodAutomaton.h PeriodAutomaton.cpp QMarkAutomaton.cpp QMarkAutomaton.h LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h "SchemesAutomaton.cpp" "SchemesAutomaton.h" "FactsAutomaton.cpp" "FactsAutomaton.h" "RulesAutomata.cpp" "RulesAutomata.h" QueriesAutomaton.cpp QueriesAutomaton.h IdAutomaton.cpp IdAutomaton.h "LineCommentAutomaton.cpp" "LineCommentAutomaton.h" "BlockCommentAutomaton.cpp" "BlockCommentAutomaton.h" StringAutomaton.cpp StringAutomaton.h "BadStringAutomaton.cpp" "BadStringAutomaton.h")
