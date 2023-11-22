# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Target executable
TARGET = opera_db

# Source files
SRCS = opera_db.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDES = -I./opera_db

# Library directories
LIBDIR = -L./opera_db

# Libraries
LIBS = -lsqlite3

# Build rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIR) -o $@ $^ $(LIBS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
