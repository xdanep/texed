##
## Created by xdanep on 20/12/23.
##

# Compiler
CC = gcc

# Libraries
LLIBS = -lncurses

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -std=gnu17

# Objects
OBJS = \
		cli.o\
		editor.o\
		file.o\
		main.o\
		screen.o\
		text.o 

# Remove command
RM = rm -f

# Targets
default: all
all: main
main: $(OBJS)
	$(CC) $(CFLAGS) -o texed $(OBJS) $(LLIBS)
clean:
	$(RM) $(OBJS) texed

install:
	install -m755 texed /usr/bin
	$(RM) $(OBJS) texed

uninstall:
	$(RM) /usr/bin/texed