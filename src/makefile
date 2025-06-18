CC = gcc
CFLAGS = --coverage -Wall -Wextra -Werror
LIBS = -lcheck -lsubunit -lm -lpthread -lgcov
#

FOLDERS=math
TEST_DIR=../tests


all: math

drop: clean
	rm -Rf $(TEST_DIR)/$(FOLDERS)

clean:
	rm -rf $(FOLDERS)/*.c.*
	rm -rf $(TEST_DIR)/$(FOLDERS)/test*.*

math: drop
	$(foreach file, $(wildcard $@/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;)
	@if [ ! -d "$(TEST_DIR)/$@" ]; then mkdir $(TEST_DIR)/$@; fi
	gcc $(CFLAGS) -c $(TEST_DIR)/test_$@.c -o $(TEST_DIR)/$@/test_$@.o
	gcc $(TEST_DIR)/$@/test_$@.o $@/*.o -o $(TEST_DIR)/$@/test_$@ $(LIBS)
	$(TEST_DIR)/$@/test_$@
	lcov --directory $(TEST_DIR)/$@ --capture -o $(TEST_DIR)/$@/coverage.info
	genhtml --output-directory $(TEST_DIR)/$@/report --legend $(TEST_DIR)/$@/coverage.info
	open $(TEST_DIR)/$@/report/index.html