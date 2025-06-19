CC=gcc
CFLAGS=--coverage -Wall -Wextra -Werror
LIBS=-lcheck -lsubunit -lm -lpthread -lgcov
CLF=clang-format

FOLDERS:=common math tests
TEST_DIR=tests

clean:
	$(foreach dir,$(FOLDERS),rm -rf $(dir)/*.c.*;)
	$(foreach dir,$(FOLDERS),rm -rf $(TEST_DIR)/$(dir)/test*.*;)

drop: clean
# $(foreach dir,$(FOLDERS),rm -Rf $(TEST_DIR)/$(dir);)
	rm -Rf $(TEST_DIR)/result
	rm -f $(TEST_DIR)/tests

clf:
	$(eval CLF=clang-format-18)

all: check tests

clang: clf all

check:
	@echo ' '
	@echo '--== Check for mistakes'
	@if [ ! -f .clang-format ]; then \
		cp ../../materials/linters/.clang-format .; \
		echo '--   .clang-format copyed'; \
	fi
	clang-format-18 -n */*.c
	clang-format-18 -n */*.h
	@echo ' ';
	cppcheck --enable=all --check-level=exhaustive --suppress=missingIncludeSystem */*.c
	@echo ' ';
	@echo '++--- clan-format -n; cppcheck; done...   press enter...'
	@read ans
	clear

tests: drop
	$(foreach fldr,$(FOLDERS),$(foreach file, $(wildcard $(fldr)/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;))
	@if [ ! -d "$(TEST_DIR)/result" ]; then mkdir $(TEST_DIR)/result; fi
	gcc */*.o -o $(TEST_DIR)/$@ $(LIBS)
	$(TEST_DIR)/$@
	lcov --directory $(TEST_DIR) --capture -o $(TEST_DIR)/result/coverage.info
	genhtml --output-directory $(TEST_DIR)/result/report --legend $(TEST_DIR)/result/coverage.info
	open $(TEST_DIR)/result/report/index.html






# $(foreach file, $(wildcard common/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;)
# $(foreach file, $(wildcard $@/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;)
# @if [ ! -d "$(TEST_DIR)/result" ]; then mkdir $(TEST_DIR)/result; fi
# gcc $(CFLAGS) -c $(TEST_DIR)/$@.c -o $(TEST_DIR)/$@.o
# gcc $(TEST_DIR)/$@.o $@/*.o common/*.o -o $(TEST_DIR)/$@/test_$@ $(LIBS)
# $(TEST_DIR)/$@/test_$@

# rm -rf $@/*.c.*
# rm -rf common/*.c.*

# lcov --directory $(TEST_DIR)/$@ --capture -o $(TEST_DIR)/$@/coverage.info
# genhtml --output-directory $(TEST_DIR)/$@/report --legend $(TEST_DIR)/$@/coverage.info
# open $(TEST_DIR)/$@/report/index.html


# basetypes:
# 	gcc $(CFLAGS) -c common/$@.c -o common/$@.c.o
# 	@if [ ! -d "$(TEST_DIR)/$@" ]; then mkdir $(TEST_DIR)/$@; fi
# 	gcc $(CFLAGS) -c $(TEST_DIR)/test_$@.c -o $(TEST_DIR)/$@/test_$@.o
# 	gcc $(TEST_DIR)/$@/test_$@.o common/$@/*.o -o $(TEST_DIR)/$@/test_$@ $(LIBS)
# 	# $(TEST_DIR)/$@/test_$@
# 	# rm -rf $@/*.c.*
# 	# rm -rf common/*.c.*
# 	# lcov --directory $(TEST_DIR)/$@ --capture -o $(TEST_DIR)/$@/coverage.info
# 	# genhtml --output-directory $(TEST_DIR)/$@/report --legend $(TEST_DIR)/$@/coverage.info
# 	# open $(TEST_DIR)/$@/report/index.html