CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lcheck -lm -lpthread -lsubunit

FOLDERS=math
TEST_DIR = ../tests

all: $(FOLDERS)

drop: clean
	rm -Rf $(TEST_DIR)/$(FOLDERS)

clean:
	rm -f $(FOLDERS)/*.o
	rm -f $(TEST_DIR)/$(FOLDERS)/*.o

math: drop
	gcc -c $@/$@.c -o $@/$@.o
	@if [ ! -d "$(TEST_DIR)/$@" ]; then mkdir $(TEST_DIR)/$@; fi
	gcc -c $(TEST_DIR)/test_$@.c -o $(TEST_DIR)/$@/test_$@.o
	gcc $(TEST_DIR)/$@/test_$@.o $@/$@.o -o $(TEST_DIR)/$@/test_$@ $(LIBS)
	$(TEST_DIR)/$@/test_$@
