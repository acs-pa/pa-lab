# SPDX-License-Identifier: BSD-3-Clause

RUSTC ?= rustc
SRC = hashmap.rs
BIN = hashmap

.PHONY: build run clean

build: $(BIN)

$(BIN): $(SRC)
	$(RUSTC) -o $(BIN) $(SRC)

run: build
	./$(BIN)

clean:
	rm -f $(BIN)
