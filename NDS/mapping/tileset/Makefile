# Tileset root Makefile node.

# Add by hand.
TOP = ..
CUR = .

PATHS=sewer


.PHONY:all clean

all:
	for dir in $(PATHS) ; do \
		make -C $$dir ; \
	done
	
	
clean:
	for dir in $(PATHS) ; do \
		make clean -C $$dir ; \
	done