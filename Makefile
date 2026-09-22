CC ?= cc
CPPFLAGS := -Isrc/include
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -Wpedantic -Wconversion -Wshadow -O2
LDFLAGS ?= -lm
SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all check clean
all: bess_demo

bess_demo: $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

check: $(OBJECTS) tests/test_bess.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o /tmp/bess_tests tests/test_bess.c $(OBJECTS) $(LDFLAGS)
	/tmp/bess_tests

clean:
	rm -f $(OBJECTS) bess_demo /tmp/bess_tests
