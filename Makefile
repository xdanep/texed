##
## Created by xdanep on 20/12/23.
##

# Compiler
CC = gcc

# Libraries
LLIBS = -lncurses

# Compiler flags
CFLAGS = -Wall -g -Wextra

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
	install -m755 /build/bin/texed /usr/bin
	mkdir -p /usr/share/licenses/texed
	install -m644 LICENSE /usr/share/licenses/texed
	rm -rf $(BUILDDIR)

uninstall:
	$(RM) /usr/bin/texed
	rm -rf /usr/share/licenses/texed