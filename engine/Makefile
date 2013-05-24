TOP = .

ENABLE_EFENCE = #ENABLED

CC = gcc
#CFLAGS := -Wall -Werror -DDEBUG
CFLAGS = -Werror -DDEBUG

TARGET = game
SOURCE = $(wildcard *.c)
OBJS = $(TOP)/libs/liblinked_list/linked_list.o #make a static lib

LDLIBS = `allegro-config --libs`\
			-lpthread\
			-lrt
LDFLAGS =

INCLUDES =	-I.\
			-I$(TOP)/util\
			-I$(TOP)/libs/liblinked_list/inc

LIB_DIR =

#LIBS = -lpthread

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
