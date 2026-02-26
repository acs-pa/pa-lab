# SPDX-License-Identifier: BSD-3-Clause
# Build and run IO example. Creates sample "in" if missing.

RUSTC ?= rustc
SRC = io.rs
BIN = io

.PHONY: build run clean

build: $(BIN)

$(BIN): $(SRC)
	$(RUSTC) -o $(BIN) $(SRC)

run: build
	@test -f in || (echo "42" > in; echo "1 2" >> in; echo "3 a hello" >> in)
	./$(BIN)

clean:
	rm -f $(BIN) in out
