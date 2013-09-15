#----------------------------------------------------------------------------------
# Copy all objects to build directory
# author: vitor.rozsa
#----------------------------------------------------------------------------------

TOP = ../
CUR = ./
COPY = cp
DESTDIR = $(TOP)/build/
OBJECTS :=	$(foreach dir,$(CUR),$(notdir $(wildcard $(dir)/*.o)))


all:
	for obj in $(OBJECTS) ; do \
		$(COPY) $$obj $(DESTDIR) ; \
	done