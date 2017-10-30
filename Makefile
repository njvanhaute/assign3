CC=gcc
CFLAGS=-Wall -Wextra -c
LDFLAGS=

SRCS=main.c bst.c queue.c cda.c
OBJS=$(SRCS:.c=.o)
EXEC=bstrees

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
