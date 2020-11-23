CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

all: alphatoe count_nodes show_node


alphatoe: alphatoe.o ttt2.o ttt1.o
	$(CC) $(CFLAGS) ttt1.o ttt2.o alphatoe.o -o alphatoe

alphatoe.o: alphatoe.c ttt.h
	$(CC) $(CFLAGS) alphatoe.c -c

show_node: show_node.o ttt2.o ttt1.o
	$(CC) $(CFLAGS) ttt1.o ttt2.o show_node.o -o show_node

show_node.o: show_node.c ttt.h
	$(CC) $(CFLAGS) show_node.c -c

count_nodes: count_nodes.o ttt2.o ttt1.o
	$(CC) $(CFLAGS) ttt1.o ttt2.o count_nodes.o -o count_nodes

count_nodes.o: count_nodes.c ttt.h
	$(CC) $(CFLAGS) count_nodes.c -c

ttt2.o: ttt2.c ttt.h
	$(CC) $(CFLAGS) ttt2.c -c

ttt1.o: ttt1.c ttt.h
	$(CC) $(CFLAGS) ttt1.c -c


clean:
	rm *.o count_nodes show_node alphatoe
