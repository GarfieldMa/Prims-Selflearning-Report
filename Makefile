CPPFLAGS=-std=c++11

test: test.cpp graph.h
	g++ $(CPPFLAGS) $< -o $@

run_test: test input.txt
	./$< < input.txt
