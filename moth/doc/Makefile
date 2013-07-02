##************************************************************************************************#
# Docummentation build
# Dependences: txt2tags; graphviz.
##************************************************************************************************#
TOPDIR = .
GRAPHDIR = $(TOPDIR)/graph

T2TC = txt2tags
CFLAGS = --toc -n --css-sugar
EXT = t2t
FORMAT = html

# moth.t2t is the index that include all the others t2t
SRC = moth.$(EXT)
TARGET = moth.$(FORMAT)

T2T_DEPS =  $(wildcard $(TOPDIR)/*.$(EXT))
GRAPH_DEPS = $(wildcard $(GRAPHDIR)/*.dot)


DEPS =	$(T2T_DEPS)\
		$(GRAPH_DEPS)

all: $(TARGET)

$(TARGET): $(DEPS)
	@make -C $(GRAPHDIR)
	$(T2TC) -o $(TARGET) -t $(FORMAT) $(CFLAGS) -i $(SRC)


.PHONY:

clean:
	rm -f *.$(FORMAT)
	@cd $(GRAPHDIR); make clean; done
