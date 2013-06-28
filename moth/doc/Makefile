##************************************************************************************************#
# Docummentation build
# Dependences: txt2tags; graphviz.
##************************************************************************************************#
TOPDIR = .
GRAPHDIR = $(TOPDIR)/graph

T2TC = txt2tags # t2t compiler
FORMAT = html # Output docummentation format
CFLAGS = --toc -n

# moth.t2t is the index that include all the others t2t
SRC = moth.t2t
TARGET = moth.html

T2T_DEPS =  $(wildcard $(TOPDIR)/*.t2t)
GRAPH_DEPS = $(wildcard $(GRAPHDIR)/*.dot)


DEPS =	$(T2T_DEPS)\
		$(GRAPH_DEPS)

all: $(TARGET)

$(TARGET): $(DEPS)
	@make -C $(GRAPHDIR)
	$(T2TC) -o $(TARGET) -t $(FORMAT) $(CFLAGS) -i $(SRC)


.PHONY:

clean:
	rm -f $(TARGET)
	@cd $(GRAPHDIR); make clean; done
