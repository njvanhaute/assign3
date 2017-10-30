CC=gcc
CFLAGS=-Wall -Wextra -c
LDFLAGS=

SRCS=main.c da.c set.c 
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
