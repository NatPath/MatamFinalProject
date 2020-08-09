CC=/usr/local/bin/gcc
#CCX=/usr/local/bin/g++
#CC=gcc
CCX=g++

EXEC=gcalc
DEBUG_FLAG=-g
COMP_FLAG=-std=c++11 -DNDEBUG -fPIC --pedantic-errors -Wall -Werror -c
OBJS_FOR_PYTHON=calc_parser.o my_utils.o MyGraph.o graph_for_python.o 
OBJS_REMAINED=Gcalc.o main.o
OBJS=$(OBJS_FOR_PYTHON) $(OBJS_REMAINED)

EXCEPTIONS_FILES=exceptions.h
MY_UTILS_FILES=my_utils.cpp my_utils.h
GCALC_FILES=Gcalc.cpp Gcalc.h
PARSER_FILES=calc_parser.cpp calc_parser.h
MYGRAPH_FILES=MyGraph.cpp MyGraph.h
MAIN_FILE=main.cpp
MAKE_FILE_FILE=Makefile
PYTHON_FILES=graph_for_python.cpp graph_for_python.h graph.i
TESTER_FILES=test_in.txt test_out.txt
DESIGN_PDF_FILE=design.pdf


ZIP_FILES=${EXCEPTIONS_FILES} ${MY_UTILS_FILES} ${GCALC_FILES} ${PARSER_FILES} ${MYGRAPH_FILES} ${PYTHON_FILES} ${TESTER_FILES} ${DESIGN_PDF_FILE}

COMPILE_OS=$(CCX) $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

$(EXEC): $(OBJS)
	$(CCX) $(OBJS) -o $@

#prepare library for python
libgraph.a: $(OBJS_FOR_PYTHON)
	ar -rs $@ $^
#zip
tar:
	zip gcalc.zip ${ZIP_FILES}

graph_for_python.o: graph_for_python.cpp graph_for_python.h calc_parser.h MyGraph.h my_utils.h
	$(COMPILE_OS)


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
	rm -f $(OBJS) $(EXEC) libgraph.a gcalc.zip 


