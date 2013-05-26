TOP = ..
MODULES = $(TOP)/modules

include $(TOP)/Makefile.header

SOURCE = $(wildcard *.c)
OBJS = $(SOURCE:.c=.o)

INCLUDES =	-I.\
			-I$(TOP)/\
			-I$(TOP)/util\
			-I$(MODULES)/linked_list/inc\
			-I$(MODULES)/alarm/inc

SOURCE:
	$(CC) $(CFLAGS) -c $(SOURCE) $(INCLUDES)


.PHONY: clean
clean:
	@echo "rm -f $(TARGET)"
	@rm -f $(TARGET)
	
#  ".PHONY" specifies that target help is not a file,
# even if there is a "help" file in the directory.
.PHONY: help
help:
	@echo "Usage: make"
	@echo "       make clean"
