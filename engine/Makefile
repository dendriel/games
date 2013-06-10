##
# Makefile for compiling all the project.
# Memory leak check: 
# "valgrind --leak-check=yes  --leak-check=full --show-reachable=yes"
# Note: Allegro game engine is a bomb of memory leaks =/
##

TOP = .
MODULES = $(TOP)/modules
SYSTEM = $(TOP)/system
VIDEO = $(TOP)/video
BRAIN = $(TOP)/brain
CONTROLLER = $(TOP)/controller
MIXEDAPI = $(MODULES)/mixedAPI

include Makefile.hd
include defines.mk

TARGET = game
INCLUDES +=	-I./system/inc

# Internal Objects Dependences #
SYSTEM_DEP = $(wildcard $(SYSTEM)/*.c)
SYSTEMDEP = $(SYSTEM_DEP:.c=.o)

VIDEO_DEP = $(wildcard $(VIDEO)/*.c)
VIDEODEP = $(VIDEO_DEP:.c=.o)

BRAIN_DEP = $(wildcard $(BRAIN)/*.c)
BRAINDEP = $(BRAIN_DEP:.c=.o)

CONTROLLER_DEP = $(wildcard $(CONTROLLER)/*.c)
CONTROLLERDEP = $(CONTROLLER_DEP:.c=.o)

MIXEDAPI_DEP = $(wildcard $(MIXEDAPI)/*.c)
MIXEDAPIDEP = $(MIXEDAPI_DEP:.c=.o)

INTOBJS =	$(SYSTEMDEP)\
			$(VIDEODEP)\
			$(BRAINDEP)\
			$(CONTROLLERDEP)\
			$(MIXEDAPIDEP)

# External Objects Dependences #
ALARMDEP = $(MODULES)/alarm/alarm.o
LINKEDLISTDEP = $(MODULES)/llist/llist.o

EXTOBJS =	$(ALARMDEP)\
			$(LINKEDLISTDEP)

# All objects #
LDOBJS =	$(INTOBJS)\
			$(EXTOBJS)


LDFLAGS =
LDLIBS = `allegro-config --libs`\
			-lpthread\
			-lrt

all: $(TARGET)

# Build target #
$(TARGET): $(SOURCE) $(VIDEODEP) $(SYSTEMDEP) $(ALARMDEP) $(MIXEDAPIDEP)
	@make -C $(VIDEO)
	@make -C $(SYSTEM)
	@make -C $(BRAIN)
	@make -C $(CONTROLLER)
	@make -C $(MIXEDAPI)
	$(CC) $(CFLAGS) $(LDOBJS) $(LDFLAGS) $(LDLIBS) $(SOURCE) $(INCLUDES) -o $(TARGET)

# Rules for dependences #
$(VIDEODEP):
	@cd $(VIDEO) && make && cd -

$(SYSTEMDEP):
	@cd $(SYSTEM) && make && cd -

$(MIXEDAPIDEP):
	@cd $(MIXEDAPI) && make && cd -



include Makefile.tl
