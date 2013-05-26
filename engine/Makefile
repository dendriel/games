TOP = .
MODULES = ./modules

include Makefile.header

TARGET = game
SOURCE = $(wildcard *.c)
OBJS =	$(MODULES)/linked_list/linked_list.o\
		$(MODULES)/alarm/alarm.o


INCLUDES =	-I.\
			-I$(TOP)/$(MODULES)/alarm/inc

LIB_DIR =


ifeq ($(ENABLE_EFENCE), ENABLED)
	LIBS += -lefence
endif


$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDES) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(TARGET)


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
