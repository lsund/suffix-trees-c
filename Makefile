CC=gcc
INCLUDE=-I'include'
CFLAGS=-std=c99 -Wall -g -D_POSIX_SOURCE -D_GNU_SOURCE $(INCLUDE)
SRC_DIR=src
TEST_DIR=test
SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c')
TEST_SRCS := $(shell find $(TEST_DIR)/* -maxdepth 0 -name '*.c')


all: dirs
	$(CC) $(INCLUDE) $(CFLAGS) $(SRCS) main.c -o bin/main -lm

test: dirs
	$(CC) $(INCLUDE) $(CFLAGS) $(SRCS) $(TEST_SRCS) -o bin/test -lm

run: all
	./bin/main

runtest: test
	./bin/test

memcheck: all
	make && valgrind --leak-check=full ./bin/main

dirs:
	mkdir -p bin
