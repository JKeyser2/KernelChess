# Makefile for chess_user_space.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Executable name
EXEC = chess_user_space

# Source files
SRCS = chess_user_space.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(EXEC) $(OBJS)

