CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined -fno-sanitize-recover=all

SRC_DIR   = src
BUILD_DIR = build
SRC       = $(wildcard $(SRC_DIR)/*.cpp)
BIN       = $(BUILD_DIR)/chess

.PHONY: all run test clean

all: $(BIN)

$(BIN): $(SRC) $(wildcard $(SRC_DIR)/*.h)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN)

test: $(BIN)
	bash tests/run_tests.sh ./$(BIN)

clean:
	rm -rf $(BUILD_DIR)
