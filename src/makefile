CC=gcc
CFLAGS=--coverage -Wall -Wextra -Werror
LIBS=-lcheck -lsubunit -lm -lpthread -lgcov
CLF=clang-format

FOLDERS:=common math
TEST_DIR=tests

clean:
	$(foreach dir,$(FOLDERS),rm -rf $(dir)/*.c.*;)
	$(foreach dir,$(FOLDERS),rm -rf $(TEST_DIR)/$(dir)/test*.*;)

drop: clean
	$(foreach dir,$(FOLDERS),rm -Rf $(TEST_DIR)/$(dir);)

clf:
	$(eval CLF=clang-format-18)

all: check math

clang: clf all

math: drop
	$(foreach file, $(wildcard common/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;)
	$(foreach file, $(wildcard $@/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;)
	@if [ ! -d "$(TEST_DIR)/$@" ]; then mkdir $(TEST_DIR)/$@; fi
	gcc $(CFLAGS) -c $(TEST_DIR)/test_$@.c -o $(TEST_DIR)/$@/test_$@.o
	gcc $(TEST_DIR)/$@/test_$@.o $@/*.o common/*.o -o $(TEST_DIR)/$@/test_$@ $(LIBS)
	$(TEST_DIR)/$@/test_$@

	$(foreach dir,$(FOLDERS),rm -rf $(dir)/*.c.*;)

	lcov --directory $(TEST_DIR)/$@ --capture -o $(TEST_DIR)/$@/coverage.info
	genhtml --output-directory $(TEST_DIR)/$@/report --legend $(TEST_DIR)/$@/coverage.info
	open $(TEST_DIR)/$@/report/index.html

check:
	@echo ' '
	@echo '--== Check for mistakes'
	@if [ ! -f .clang-format ]; then \
		cp ../../materials/linters/.clang-format .; \
		echo '--   .clang-format copyed'; \
	fi
# $(foreach dir,$(FOLDERS),$(CLF) -i $(dir)/*.c; $(CLF) -i $(dir)/*.h;)
	$(foreach dir,$(FOLDERS),$(CLF) -n $(dir)/*.c; $(CLF) -n $(dir)/*.h;)
	@echo ' ';
	cppcheck --enable=all --check-level=exhaustive --suppress=missingIncludeSystem */*.c
	@echo ' ';
	@echo '--   press enter...'
	@read ans
	# clear