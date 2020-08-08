CC=/usr/local/bin/gcc
CCX=/usr/local/bin/g++
#CC=gcc
#CCX=g++

EXEC=gcalc
DEBUG_FLAG=-g
COMP_FLAG=-std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -c
OBJS_FOR_PYTHON=calc_parser.o my_utils.o MyGraph.o 
OBJS_REMAINED=Gcalc.o main.o
OBJS=$(OBJS_FOR_PYTHON) $(OBJS_REMAINED)

COMPILE_OS=$(CCX) $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
$(EXEC): $(OBJS)
	$(CCX) $(OBJS) -o $@

my_utils.o: my_utils.cpp my_utils.h exceptions.h
	$(COMPILE_OS)

MyGraph.o: MyGraph.cpp MyGraph.h my_utils.h exceptions.h
	$(COMPILE_OS)

calc_parser.o: calc_parser.cpp calc_parser.h my_utils.h exceptions.h MyGraph.h
	$(COMPILE_OS)

main.o: main.cpp my_utils.h Gcalc.h MyGraph.h exceptions.h
	$(COMPILE_OS)

Gcalc.o: Gcalc.cpp Gcalc.h my_utils.h MyGraph.h exceptions.h calc_parser.h
	$(COMPILE_OS)


clean:
	rm -f $(OBJS) $(EXEC)


