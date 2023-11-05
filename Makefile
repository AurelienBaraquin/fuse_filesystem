CC = gcc
CFLAGS = -Wall -g3 $(shell pkg-config fuse3 --cflags) -Iinclude
LDFLAGS = $(shell pkg-config fuse3 --libs) -lz

CHECK_CFLAGS = $(shell pkg-config --cflags check)
CHECK_LDFLAGS = $(shell pkg-config --libs check)

SRCDIR = src
TESTDIR = tests
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(SOURCES:.c=.o)
TEST_SOURCES = $(shell find $(TESTDIR) -name '*_test.c')
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
EXECUTABLE = myfuse
TEST_EXECUTABLE = run_unitests


# MOUNTPOINT _________________________________________________________________

MOUNTPOINT = mount_dir

# ____________________________________________________________________________


FUSE_TEST_EXECUTABLE = fuse_test.pl

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) -c $< -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(filter-out $(SRCDIR)/main.o, $(OBJECTS))
	$(CC) $^ -o $@ $(CHECK_LDFLAGS) $(LDFLAGS)

run : $(EXECUTABLE)
	mkdir -p $(MOUNTPOINT)
	./$(EXECUTABLE) -o allow_other -o clone_fd $(MOUNTPOINT)

unitest: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)
	@echo "Tests completed."

fusetest: $(EXECUTABLE)
	perl $(TESTDIR)/$(FUSE_TEST_EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TEST_OBJECTS) $(TEST_EXECUTABLE)

re: clean all

.PHONY: all clean re run_tests
