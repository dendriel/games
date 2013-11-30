#----------------------------------------------------------------------------------
# Auto build tileset data from a .png file. Keep only 1 png file per folder.
# Collision map must be made by hand.
# This is a generic Makefile. Put in the tileset folder and add the folder name into
# the root Makefile.
# author: vitor.rozsa
#----------------------------------------------------------------------------------

GRIT=C:/devkitPro/devkitARM/bin/grit.exe
FLAGS=-mR8 -gB8 -gS -pS -fa
FLAGS2= -mz! -gz! -pz! -gTFF00FF -ftc

SOURCE=$(wildcard *.png)
TARGET_NAME=$(SOURCE:.png=)_data
APPEND=echo "\#include \"$(TARGET_NAME).h\""

TARGET=$(TARGET_NAME).cpp $(TARGET_NAME).h 


#grit image.bmp -mR8 -gB8 -gS -pS -fa -o tileset_name -mz! -gz! -pz! -gTFF00FF -ftc

all:$(TARGET)

$(TARGET):$(SOURCE)
	@make clean
	$(GRIT) $(SOURCE) $(FLAGS) -o $(TARGET_NAME) $(FLAGS2)
	$(APPEND) >> $(TARGET_NAME).cpp
	cat $(TARGET_NAME).c >> $(TARGET_NAME).cpp
	rm -f $(TARGET_NAME).c
	

.PHONY:clean

# Clean data files and create a dummy file.
clean:
	@rm -f $(TARGET_NAME).cpp $(TARGET_NAME).h
	@touch $(TARGET_NAME).cpp