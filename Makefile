CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic-errors

FILES = HashTable.hpp $(wildcard include/Abstract/*.hpp include/BinaryTree/*.hpp include/BinaryTreeDictionary/*.hpp)
TEMPLATES = $(wildcard src/BinaryTree/*.tpp src/BinarytreeDictionary/*.tpp)
GTEST = external/googletest/googletest

.PHONY: all test

all:
	$(CXX) $(CXXFLAGS) -fsyntax-only -x c++ $(FILES)

main: main.cpp
	$(CXX) $(CXXFLAGS) -I. main.cpp -o main

tree_tests: tests.cpp $(FILES) $(TEMPLATES)
	$(CXX) $(CXXFLAGS) -I. -I$(GTEST)/include -I$(GTEST) tests.cpp $(GTEST)/src/gtest-all.cc $(GTEST)/src/gtest_main.cc -pthread -o tree_tests

test: tree_tests
	./tree_tests
