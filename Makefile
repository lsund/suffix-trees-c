CC=gcc
INCLUDE=-I'include'
CFLAGS=-std=c99 -Wall -g -D_POSIX_SOURCE -D_GNU_SOURCE $(INCLUDE)
SRC_DIR=src
# TEST_DIR=tests
SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c')
# TEST_SRCS := $(shell find $(TEST_DIR)/* -maxdepth 0 -name '*.c')


all: dirs
	$(CC) $(INCLUDE) $(CFLAGS) $(SRCS) -o bin/main -lm

run: all
	./bin/main

dirs:
	mkdir -p bin
