CC = g++
CFLAGS = -Wall
OBJS = src/main.o
PROG = game 
LDLIBS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)

clean:
	rm -f src/*.o $(PROG)
