##
## Created by xdanep on 20/12/23.
##

# Compiler
CC = gcc

# Libraries
LLIBS = -lncurses

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -std=gnu17 -O2 -DNDEBUG

# Directories
SRCDIR = src
BUILDDIR = build
TARGET = build/bin/texed
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Objects
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Remove command
RM = rm -f

# Targets
default: all
all: $(TARGET)
# Rule for executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LLIBS)

# Rule for objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/bin

clean:
	rm -rf $(BUILDDIR)

install:
	install -m755 texed /usr/bin
	rm -rf $(BUILDDIR)

uninstall:
	$(RM) /usr/bin/texed