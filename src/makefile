CC=gcc
CFLAGS=--coverage -Wall -Wextra -Werror
LIBS=-lcheck -lsubunit -lm -lpthread -lgcov
CLF=clang-format
FOLDERS:=. common s21_trim s21_insert s21_to_lower s21_to_upper s21_sprintf s21_strerror s21_strtok s21_strrchr s21_memcmp s21_memcpy s21_memset s21_strstr s21_strcspn s21_strpbrk s21_strlen s21_strncmp s21_memchr s21_strncpy s21_strchr s21_strncat
OBJECTS=$(foreach fldr,$(FOLDERS),$(foreach file, $(wildcard $(fldr)/*.c), $(file).o))
TEST_DIR=test

all: check test

clean:
	$(foreach dir,$(FOLDERS),rm -rf $(dir)/*.c.*;)
	rm -rf $(TEST_DIR)/*.c.*
	rm -Rf $(TEST_DIR)/result
	rm -f $(TEST_DIR)/$(TEST_DIR)
	rm -f *.a

clf:
	$(eval CLF=clang-format-18)

clang: clf all

check:
	@echo ' '
	@echo '--== Check for mistakes'
	@if [ ! -f .clang-format ]; then \
		cp ../../materials/linters/.clang-format .; \
		echo '--   .clang-format copyed'; \
	fi

	$(CLF) -n */*.c
	$(CLF) -n */*.h
	@echo ' ';
	cppcheck --enable=all --check-level=exhaustive --suppress=missingIncludeSystem */*.c
	@echo ' ';
	@echo '++--- clan-format -n; cppcheck; done...   press enter...'
	@read ans
	clear

test: clean
	$(foreach fldr,$(FOLDERS),$(foreach file, $(wildcard $(fldr)/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;))
	$(foreach file, $(wildcard $(TEST_DIR)/*.c), gcc $(CFLAGS) -c $(file) -o $(file).o;)
	@if [ ! -d "$(TEST_DIR)/result" ]; then mkdir $(TEST_DIR)/result; fi
	gcc *.o */*.o -o $(TEST_DIR)/$@ $(LIBS)
	$(TEST_DIR)/$@

gcov_report:
	lcov --directory $(TEST_DIR) --capture -o $(TEST_DIR)/result/coverage.info
	genhtml --output-directory $(TEST_DIR)/result/report --legend $(TEST_DIR)/result/coverage.info
# open $(TEST_DIR)/result/report/index.html

s21_string.a: $(OBJECTS)
	rm -f $@
	ar rcs $@ $^
	rm -rf $^

$(OBJECTS): %.c.o: %.c
	$(CC) -Wall -Wextra -Werror -c $^ -o $@