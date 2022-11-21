default_target: all 
.PHONY : default_target

$(VERBOSE).SILENT:

SHELL = /bin/sh

all: 
	clear
	cd build && cmake .. && make -j8
	cd build && ./main $(algorithm) $(test_function)
.PHONY: all 