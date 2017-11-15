CC=gcc
CFLAGS=-Wall -Wextra -c
LDFLAGS=

SRCS=main.c args.c bst.c cda.c da.c edge.c integer.c rbt.c scanner.c set.c queue.c utils.c
OBJS=$(SRCS:.c=.o)
EXEC=kruskal

all : $(EXEC) $(SRCS)

$(EXEC) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean test
clean :
	rm -f $(EXEC) $(OBJS)

test : $(EXEC)
	./$(EXEC)
