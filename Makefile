CC = gcc
CFLAGS = -Wall -g3 $(shell pkg-config fuse3 --cflags) -Iinclude
LDFLAGS = $(shell pkg-config fuse3 --libs)

SRCDIR = src
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = myfuse

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

re : clean all