##
# Makefile for compiling libsystem
# Author: vitor.rozsa
# date: 21/05/2013
##

DIR_TOP := ../..

COMPILER = gcc

TARGET = libsystem.a

SOURCE := $(wildcard *.c)
OBJECTS := $(SOURCE:.c=.o)
#OBJECTS:= system.o
INCLUDES := -I./


$(TARGET): $(OBJECTS)
	@echo "Creating the static library..."
	ar rcs $(TARGET) $(OBJECTS)

$(OBJECTS):
	@echo "Compiling objects..."
	$(COMPILER) -c $(SOURCE)


.PHONY: clean
clean:
	@echo "Clean..."
	@echo "rm -f $(TARGET)"
	@rm -f $(TARGET)
	@echo "rm -f $(OBJECTS)"
	@rm -f $(OBJECTS)

#  ".PHONY" specifies that target help is not a file,
# even if there is a "help" file in the directory.
.PHONY: help
help:
	@echo "Usage: make"
	@echo "       make clean"
