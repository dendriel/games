#----------------------------------------------------------------------------------
# Transform
# author: vitor.rozsa
#----------------------------------------------------------------------------------

TOP=../
CUR=./
GRIT=C:/devkitPro/devkitARM/bin/grit.exe
FLAGS=-pS -m! -gB8 -ftc -gB16 -fa
FLAGS2=-Mh4 -Mw4 -gTFF00FF

SOURCE=$(wildcard ./*.bmp)
TARGET_NAME=sprites_data
APPEND=echo "\#include \"$(TARGET_NAME).h\""

TARGET=$(TARGET_NAME).cpp $(TARGET_NAME).h


all: $(TARGET)

$(TARGET): $(SOURCE)
	$(GRIT) $(SOURCE) $(FLAGS) -o $(TARGET_NAME) $(FLAGS2)
	$(APPEND) >> $(TARGET_NAME).cpp
	cat $(TARGET_NAME).c >> $(TARGET_NAME).cpp
	rm -f $(TARGET_NAME).c
	
	
.PHONY:clean

clean:
	rm -f $(TARGET_NAME).cpp $(TARGET_NAME).h
	#dummy file
	echo "" > $(TARGET_NAME).cpp