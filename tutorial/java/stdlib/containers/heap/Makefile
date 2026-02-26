# SPDX-License-Identifier: BSD-3-Clause

JAVAC ?= javac
JAVA ?= java
MINHEAP = MinHeap.java
MAXHEAP = MaxHeap.java

.PHONY: run run-min run-max clean

run: run-min run-max

run-min: MinHeap.class
	$(JAVA) MinHeap

run-max: MaxHeap.class
	$(JAVA) MaxHeap

MinHeap.class: $(MINHEAP)
	$(JAVAC) $(MINHEAP)

MaxHeap.class: $(MAXHEAP)
	$(JAVAC) $(MAXHEAP)

clean:
	rm -f MinHeap.class MaxHeap.class
