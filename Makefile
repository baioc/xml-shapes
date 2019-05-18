# Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
APP_NAME=xml-images

CC = g++
CFLAGS = -std=c++11 -I.

TEST_CFLAGS = -Wall -fsanitize=leak -Werror
DEBUG_CFLAGS = $(TEST_CFLAGS) -D DEBUG -O0
BUILD_CFLAGS = -D NDEBUG -O2

TARGET = src/main.cpp
DEPS = $(TARGET) src/linked_stack.h src/linked_stack.inc src/linked_queue.h src/linked_queue.inc

default: $(DEPS)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -o $(APP_NAME).out $(TARGET)

test:
	make default
	./$(APP_NAME).out

debug: $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -o $(APP_NAME).out -g $(TARGET)
	gdb $(APP_NAME).out

build: $(DEPS)
	$(CC) $(CFLAGS) $(BUILD_CFLAGS) -o $(APP_NAME).out $(TARGET)

clean:
	rm *.out
