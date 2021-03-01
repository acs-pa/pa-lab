# Darius-Florentin Neațu (neatudarius@gmail.com)

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Werror=vla
LDFLAGS = -lm

SRCS = $(sort $(wildcard *.cpp))
TARGETS = $(patsubst %.cpp,%,$(SRCS))

# build all targets
all: $(TARGETS)

# general rule for building a target
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# clean all related target files
clean:
	rm -f *.o $(TARGETS)

# pack directory
pack:
	zip -FS $(ZIP).zip *.cpp *.h Makefile README

.PHONY: pack clean
