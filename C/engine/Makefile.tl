# Generic Makefile for compiling objects [tail].

$(OBJS): $(SOURCE) $(INCDEP)
ifdef DEPOBJS
	@make -C $(DEPDIR)
endif
	$(CC) $(CFLAGS) -c $(INCLUDES) $(SOURCE)

.PHONY: clean
clean:
	@echo "rm -f $(OBJS)"
	@rm -f $(OBJS)
ifdef DEPOBJS
	@echo "rm -f $(DEPOBJS)"
	@rm -f $(DEPOBJS)
endif
ifdef TARGET
	@echo "rm -f $(TARGET)"
	@rm -f $(TARGET)
	@echo "rm -f $(INTOBJS)"
	@rm -f $(INTOBJS)
endif
	
#  ".PHONY" specifies that target help is not a file,
# even if there is a "help" file in the directory.
.PHONY: help
help:
	@echo "Usage: make"
	@echo "       make clean"
