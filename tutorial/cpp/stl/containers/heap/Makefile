# SPDX-License-Identifier: BSD-3-Clause

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Werror=vla
LDFLAGS = -lm

.PHONY: all run run-min run-max clean

all: minheap maxheap

minheap: minheap.cpp
	$(CC) $(CFLAGS) -o minheap minheap.cpp $(LDFLAGS)

maxheap: maxheap.cpp
	$(CC) $(CFLAGS) -o maxheap maxheap.cpp $(LDFLAGS)

run: run-min run-max

run-min: minheap
	./minheap

run-max: maxheap
	./maxheap

clean:
	rm -f minheap maxheap
