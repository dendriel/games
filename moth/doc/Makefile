# Docummentation build

T2TC = txt2tags # t2t compiler
FORMAT = html # Output docummentation format
CFLAGS = --toc -n

# moth.t2t is the index that include all the others t2t
SRC = moth.t2t
DEPS = $(wildcard ./*.t2t)
TARGET = moth.html

all: $(TARGET)

$(TARGET): $(DEPS)
	$(T2TC) -o $(TARGET) -t $(FORMAT) $(CFLAGS) -i $(SRC)


.PHONY:

clean:
	rm -f $(TARGET)
