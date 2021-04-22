EXEC = dijkstra
CC = g++ -O4
CFLAGS = -c -Wall
# $(EXEC) has the value of shell variable EXEC, which is run.
# run depends on the files main.o util.o heap.o
$(EXEC) :main.o util.o heap.o graph.o
# run is created by the command g++ -o run main.o util.o
# note that the TAB before $(CC) is REQUIRED...
	$(CC) -o $(EXEC) main.o util.o heap.o graph.o
# main.o depends on the files main.h main.cpp
main.o :main.cpp util.h heap.h graph.h
	$(CC) $(CFLAGS) main.cpp
util.o :util.cpp util.h heap.h graph.h
	$(CC) $(CFLAGS) util.cpp
heap.o :heap.cpp util.h heap.h graph.h
	$(CC) $(CFLAGS) heap.cpp
graph.o :graph.cpp util.h heap.h graph.h
	$(CC) $(CFLAGS) graph.cpp
clean :
	rm *.o