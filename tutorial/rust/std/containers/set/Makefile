# SPDX-License-Identifier: BSD-3-Clause
# Targets: run (BTreeSet), run-unordered (HashSet), clean

RUSTC ?= rustc

.PHONY: build run run-unordered clean

build: set unordered_set

set: set.rs
	$(RUSTC) -o set set.rs

unordered_set: unordered_set.rs
	$(RUSTC) -o unordered_set unordered_set.rs

run: set
	./set

run-unordered: unordered_set
	./unordered_set

clean:
	rm -f set unordered_set
