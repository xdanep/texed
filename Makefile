##
## Created by xdanep on 20/12/23.
##

all:
	-echo "Building..."
	@make -C ./src

clean:
	@make -C ./src clean

install: all
	@make -C ./src install

uninstall:
	@make -C ./src uninstall
