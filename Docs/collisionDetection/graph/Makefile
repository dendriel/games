# Compile dot graphs
BUILDER=dot
FORMAT=png
FLAGS=-O
DEPS = $(wildcard ./*.dot)
TARGET = $(DEPS:.dot=.dot.png)


all: $(TARGET)

$(TARGET): $(DEPS)
	$(BUILDER) $(FLAGS) -T$(FORMAT) $(DEPS)


.PHONY:

#clean:
#	rm -f *.png
