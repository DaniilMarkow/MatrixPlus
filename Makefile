UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CXX = clang++
    CXXFLAGS_BASE = -Wall -Werror -Wextra -g -std=c++20 -stdlib=libc++
    LDFLAGS_BASE = -pthread -stdlib=libc++
    COVERAGE_CFLAGS = -fprofile-instr-generate -fcoverage-mapping
    COVERAGE_LDFLAGS = -fprofile-instr-generate -fcoverage-mapping
    GTEST_INC = /Users/ricottai/.brew/Cellar/googletest/1.17.0/include
    GTEST_LIB = /Users/ricottai/.brew/Cellar/googletest/1.17.0/lib
    GTEST_INCLUDE = -I$(GTEST_INC)
    GTEST_LIBS = -L$(GTEST_LIB) -lgtest -lgtest_main
    LLVM_PROFDATA = $(shell xcrun -f llvm-profdata)
    LLVM_COV = $(shell xcrun -f llvm-cov)
else
    CXX = g++
    CXXFLAGS_BASE = -Wall -Werror -Wextra -g -std=c++20
    LDFLAGS_BASE = -pthread
    COVERAGE_CFLAGS = -fprofile-arcs -ftest-coverage
    COVERAGE_LDFLAGS = --coverage
    GTEST_CFLAGS = $(shell pkg-config --cflags gtest_main)
    GTEST_LDFLAGS = $(shell pkg-config --libs gtest_main)
    GTEST_INCLUDE = $(GTEST_CFLAGS)
    GTEST_LIBS = $(GTEST_LDFLAGS)
endif

CXXFLAGS = $(CXXFLAGS_BASE) $(GTEST_INCLUDE) $(COVERAGE_CFLAGS)
LDFLAGS = $(LDFLAGS_BASE) $(COVERAGE_LDFLAGS) $(GTEST_LIBS)
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer
ASAN_EXEC = $(OBJ_DIR)/s21_test_matrix_asan

SRC_DIR = .
TEST_DIR = tests
OBJ_DIR = build
GCOV_DIR = gcov_report
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
LIB = $(OBJ_DIR)/s21_matrix_oop.a
TEST_EXEC = $(OBJ_DIR)/s21_test_matrix
GCOV_TEST_EXEC = $(OBJ_DIR)/s21_test_matrix_gcov

all: $(LIB)

s21_matrix_oop.a: all

$(LIB): $(OBJ_FILES)
	@mkdir -p $(@D)
	@ar rc $@ $^
	@ranlib $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

test: $(LIB)
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(TEST_FILES) $(LIB) $(LDFLAGS) -o $(TEST_EXEC)
	@if [ -f $(TEST_EXEC) ]; then ./$(TEST_EXEC); else echo "Test executable not created"; fi

$(GCOV_TEST_EXEC): $(SRC_FILES) $(TEST_FILES)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(TEST_FILES) $(SRC_FILES) $(LDFLAGS) -o $@

gcov_report: $(GCOV_TEST_EXEC)
	@mkdir -p $(GCOV_DIR)
ifeq ($(UNAME_S),Darwin)
	@LLVM_PROFILE_FILE="$(OBJ_DIR)/coverage.profraw" ./$(GCOV_TEST_EXEC)
	@$(LLVM_PROFDATA) merge -sparse "$(OBJ_DIR)/coverage.profraw" -o "$(OBJ_DIR)/coverage.profdata"
	@$(LLVM_COV) show ./$(GCOV_TEST_EXEC) \
	    -instr-profile="$(OBJ_DIR)/coverage.profdata" \
	    -format=html \
	    -output-dir="$(GCOV_DIR)" \
	    -ignore-filename-regex='.*/googletest/.*|.*/tests/.*'
	@open "$(GCOV_DIR)/index.html"
else
	@rm -f *.gcno *.gcda
	@./$(GCOV_TEST_EXEC)
	@lcov --rc branch_coverage=1 --rc geninfo_no_exception_branch=1 --ignore-errors mismatch,mismatch,source,unused,inconsistent --capture --directory . --output-file $(GCOV_DIR)/coverage.info --no-external
	@genhtml $(GCOV_DIR)/coverage.info --output-directory $(GCOV_DIR) --rc genhtml_branch_coverage=1 --ignore-errors mismatch,mismatch,source,unused,inconsistent
	@xdg-open $(GCOV_DIR)/index.html 2>/dev/null || true
endif

test_valgrind: test
ifeq ($(UNAME_S),Darwin)
	@echo "Valgrind not recommended on macOS. Using AddressSanitizer instead"
	@$(MAKE) test_asan
else
	@mkdir -p ./logs
	@valgrind --tool=memcheck --leak-check=full \
	          --log-file=./logs/valgrind_log.txt ./$(TEST_EXEC)
endif

test_asan: $(LIB)
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(ASAN_FLAGS) $(TEST_FILES) $(LIB) $(LDFLAGS) -fsanitize=address -o $(ASAN_EXEC)
	@./$(ASAN_EXEC)

clean:
	@rm -rf $(OBJ_DIR) $(GCOV_DIR) *.gcno *.gcda *.info ./logs *.profraw

style:
	@clang-format -i -style=google $(SRC_DIR)/*.cpp $(TEST_DIR)/*.cpp *.h

test_style:
	@clang-format -n -style=google $(SRC_DIR)/*.cpp $(TEST_DIR)/*.cpp *.h

test_cppcheck:
	cppcheck --enable=all --inconclusive --std=c++20 --suppress=missingIncludeSystem -I . $(SRC_DIR)/*.cpp $(TEST_DIR)/*.cpp

clean_coverage:
	@find . -name '*.gcda' -delete
	@rm -rf $(GCOV_DIR)

.PHONY: all clean test gcov_report style test_style test_valgrind test_cppcheck s21_matrix_oop.a