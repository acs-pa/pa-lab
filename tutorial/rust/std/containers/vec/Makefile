# SPDX-License-Identifier: BSD-3-Clause

RUSTC ?= rustc
SRC = vec.rs
BIN = vec

.PHONY: build run clean

build: $(BIN)

$(BIN): $(SRC)
	$(RUSTC) -o $(BIN) $(SRC)

run: build
	./$(BIN)

clean:
	rm -f $(BIN)
