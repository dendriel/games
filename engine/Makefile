TOP = .

ENABLE_EFENCE := #ENABLED

CC = gcc
CFLAGS := -Wall -Werror -DDEBUG_ON

TARGET := game
SOURCE := $(wildcard *.c)

LDLIBS = `allegro-config --libs`\
			-lpthread
LDFLAGS =

INCLUDES =	-I.\
			-I$(TOP)/util

LIB_DIR :=

#LIBS = -lpthread

ifeq ($(ENABLE_EFENCE), ENABLED)
	LIBS += -lefence
endif


$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDES) $(LDFLAGS) $(LDLIBS) -o $(TARGET)


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
