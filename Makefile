default_target: all 
.PHONY : default_target

$(VERBOSE).SILENT:

SHELL = /bin/sh

all: 
	clear
	cd build && make -j8
	cd build && ./main
.PHONY: all 