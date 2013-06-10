TOP = ..
MODULES = $(TOP)/modules

include $(TOP)/Makefile.hd

ACTIONS = ./actions

ACTIONS_DEP = $(wildcard $(ACTIONS)/*.c)
ACTIONSDEP = $(ACTIONS_DEP:.c=.o)
ACTIONSINCDEP = $(ACTIONS)/inc

DEPOBJS = $(ACTIONSDEP)
INCDEP += $(ACTIONSINCDEP)
DEPDIR = $(ACTIONS)

INCLUDES +=	-I$(TOP)/inc\
			-I./actions/inc\
			-I$(TOP)/video/inc\
			-I$(TOP)/brain/inc\
			-I$(TOP)/system/inc\
			-I$(TOP)/util\
			-I$(MODULES)/mixedAPI/inc\
			-I$(MODULES)/llist/inc

include $(TOP)/Makefile.tl
