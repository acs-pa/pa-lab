# SPDX-License-Identifier: BSD-3-Clause

RUSTC ?= rustc
SRC = stack.rs
BIN = stack

.PHONY: build run clean

build: $(BIN)

$(BIN): $(SRC)
	$(RUSTC) -o $(BIN) $(SRC)

run: build
	./$(BIN)

clean:
	rm -f $(BIN)
