#----------------------------------------------------------------------------------
# Auto build map data from a .txt file using the convTool.
# author: vitor.rozsa
#----------------------------------------------------------------------------------

TOP=../..
TILESET_DIR=$(TOP)/tileset
TXT=TXT
CONVTOOL=$(TOP)/misc/tools/convTool.exe
SOURCE=$(wildcard *.$(TXT))

RAW=$(SOURCE:.$(TXT)=)
TARGET=$(SOURCE:.$(TXT)=.cpp)
TARGET+=$(SOURCE:.$(TXT)=.h)

MAP_WIDTH=70
TILESET=$(TILESET_DIR)/sewer/sewer_tileset_data.cpp
TILESET_SIZE=8

all:$(TARGET)

$(TARGET):$(SOURCE)
	for map in $(RAW) ; do \
		$(CONVTOOL) -i $$map.$(TXT) -w $(MAP_WIDTH) -t $(TILESET) -s $(TILESET_SIZE) -o $$map; \
	done


.PHONY:clean

clean:
	@rm -rf $(TARGET)
	@for dummy in $(RAW) ; do \
		touch $$dummy.cpp; \
	done