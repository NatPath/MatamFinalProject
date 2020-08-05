
CC=g++
EXEC=parser_test
COMP_FLAG= -std=c++11 -Wall -Werror -pedantic-errors

INCLUDE_DIR=../include
INCLUDE=-I $(INCLUDE_DIR)

CPP_FILES=parser_tester.cpp calc_parser.cpp ../my_utils/my_utils.cpp
OBJS=calc_parser.o parser_tester.o my_utils.o


COMPILE_OS=$(CC) $(DEBUG_FLAGS) $(COMP_FLAG) $(INCLUDE) $(CPP_FILES)

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(OBJS) -o $@

calc_parser.o: calc_parser.c calc_parser.h
	$(COMPILE_OS)

