BIN_DIR=bin
SOURCE_DIR=tests
INCLUDE_DIR=.

CXXFLAGS=-std=c++14
CCFLAGS=-O0 -Wall -Werror -Wpedantic -I$(INCLUDE_DIR) -I$(SOURCE_DIR)
CXX=g++-9
CC=gcc-9

SUCCESS_TEXT=\033[92m
FAILURE_TEXT=\033[91m
NORMAL_TEXT=\033[0m

TESTS_EXECUTABLE=$(BIN_DIR)/run_tests

.PHONY: all clean build

all: clean build
	@./$(TESTS_EXECUTABLE) \
		&& echo "\n$(SUCCESS_TEXT)Tests were successful!$(NORMAL_TEXT)" \
		|| echo "\n$(FAILURE_TEXT)One or more tests failed!$(NORMAL_TEXT)";

clean:
	rm -rfv $(TESTS_EXECUTABLE) $(SOURCE_DIR)/**/*.o

build: $(TESTS_EXECUTABLE)

$(TESTS_EXECUTABLE): $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(CCFLAGS) $(SOURCE_DIR)/tests.cc -o $(TESTS_EXECUTABLE)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
