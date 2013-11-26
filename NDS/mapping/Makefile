#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing binary data
# INCLUDES is a list of directories containing extra header files
# GRAPHICS is a list of directories containing files to be processed by grit
# AUDIO is a list of directories containing files to be processed by mmutil
# SOUNDBANK_NAME is the name of the maxmod generated soundbank
# SPRITES Game objects sprites
# TILESETS Game scenery maps tilesets
#
# All directories are specified relative to the project directory where
# the makefile is found.
#
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	game_control misc sprites\
				game_play\
				game_play/base\
				game_play/character\
				game_play/objects\
				game_play/scenery\
				game_play/inventory\
				misc/gpos\
				tileset/sewer\
				map/sewer

DATA		:= 
INCLUDES	:=	include sprites\
				misc/gpos/include\
				game_control/include\
				game_play/base/include\
				game_play/include\
				game_play/character/include\
				game_play/scenery\
				game_play/objects/include\
				game_play/inventory/include\
				game_play/trigger/include

# Maps
INCLUDES += map\
			map/sewer

# Tilesets
INCLUDES += tileset\
			tileset/sewer


GRAPHICS	:=	gfx
SPRITES		:=  sprites
AUDIO		:=	audio
SOUNDBANK_NAME  :=	soundbank
SPRITES		:= sprites
TILESETS	:= tileset

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb -mthumb-interwork

CFLAGS	:=	-g -Wall -Werror -O2\
 		-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
		-ffast-math \
		$(ARCH)
		#std=gnu++11

CFLAGS	+=	$(INCLUDE) -DARM9
CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)


#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lmm9 -lnds9
 
 
#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(LIBNDS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------
 
export OUTPUT	:=	$(CURDIR)/$(TARGET)
 
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
			$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir)) \
			$(foreach dir,$(AUDIO),$(CURDIR)/$(dir))\
			$(foreach dir,$(SPRITES),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*))) $(SOUNDBANK_NAME).bin
PNGFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.png)))
BMPFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.bmp)))
SPRITE_FILES   :=  $(foreach dir, $(SPRITES),$(notdir $(wildcard $(dir)/*.png)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES		:=	$(addsuffix .o,$(BINFILES)) \
				$(PNGFILES:.png=.o) \
				$(BMPFILES:.bmp=.o) \
				$(CPPFILES:.cpp=.o) \
				$(SFILES:.s=.o)

export AUDIOFILES	:=	$(foreach dir,$(AUDIO),$(notdir $(wildcard $(dir)/*)))
 
export INCLUDE		:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
				$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
				$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
				-I$(CURDIR)/$(BUILD)
 
export LIBPATHS		:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean
 
#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	make -C $(SPRITES)
	make -C $(TILESETS)
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
 
#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).arm9
	@make clean -C $(SPRITES)
	@make clean -C $(TILESETS)
 
 
#---------------------------------------------------------------------------------
else
 
#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).nds	: 	$(OUTPUT).arm9
$(OUTPUT).arm9	:	$(OUTPUT).elf
$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------
%.s %.h : %.png
	grit $< -ff../sprites/sprite.grit -o$*

#---------------------------------------------------------------------------------
# The bin2o rule should be copied and modified
# for each extension used in the data directories
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# This rule creates object files from binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	: %.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# This rule creates assembly source files using grit.
# grit takes an image file and a .grit file describing how the file is to be
# processed.
#---------------------------------------------------------------------------------
%.s %.h	: %.png %.grit
#---------------------------------------------------------------------------------
	grit $< -fts -o$*

#---------------------------------------------------------------------------------
# This rule creates the soundbank file for your project using mmutil.
# mmutil takes all audio files in the audio folder and puts them into a
# soundbank file.
#---------------------------------------------------------------------------------
$(SOUNDBANK_NAME).bin : $(AUDIOFILES)
#---------------------------------------------------------------------------------
	@echo $(notdir $^)
	@mmutil -d $^ -o$(SOUNDBANK_NAME).bin -h$(SOUNDBANK_NAME).h

 
-include $(DEPSDIR)/*.d
 
#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
