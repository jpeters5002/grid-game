# compiler
CC = g++
CFLAGS = -Wall
LDLIBS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
COMPILE.cpp = $(CC) $(CFLAGS) -c -o $@

# dirs
OUTPUT = build
OBJ = obj
SRC = src

# files
OBJECTS := $(wildcard $(SRC)/*.cpp)
HEADERS := $(wildcard $(SRC)/*.hpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp))
PROG = $(OUTPUT)/game 

all: $(PROG)
	echo "objs: $(OBJECTS)"

$(OUTPUT):
	mkdir -p $(OUTPUT)

$(OBJ):
	mkdir -p $(OBJ)

$(PROG): $(OBJECTS) $(OUTPUT)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	$(COMPILE.cpp) $<

run: $(PROG)
	./$(PROG)

clean:
	rm -f $(OUTPUT)/* $(OBJ)/* && rmdir $(OUTPUT) $(OBJ)
