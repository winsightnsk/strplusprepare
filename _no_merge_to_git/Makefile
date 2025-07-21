CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -L../src
LDLIBS = -l:s21_string.a
# INCLUDES = -I. -I../src

TARGET = test
SRC = test.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: makeit runit

runit:
	valgrind --tool=memcheck --leak-check=yes ./test

makeit: $(TARGET)

$(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
	rm -f test