.PHONY: all clean
TargetOS = lin
CC = g++
OBJ = obj/main.o obj/settings.o obj/gui.o obj/gameScreens.o
OUTPUT = main
OBJPATH = obj/
SOURCEPATH = src/

ifeq ($(OS),Windows_NT)
	TargetOS = win
	CC = g++
else
	UNAMEOS = $(shell uname)
	ifeq ($(UNAMEOS),Linux)
		TargetOS = lin
		CC = g++
	endif
	ifeq ($(UNAMEOS),Darwin)
		TargetOS = osx
		CC = clang
	endif
endif



all: $(TargetOS)
clean: $(TargetOS)clean

winclean:
	del /S "obj\*.o"
	del $(OUTPUT).exe
osxclean: linclean
linclean:
	rm -fr $(OBJPATH)*.o $(OUTPUT).game

win: $(OUTPUT)
	./$(OUTPUT)
lin: $(OUTPUT).game
	./$(OUTPUT).game
osx: sorry

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -Llib -lraylib -lgdi32 -lwinmm -o $(OUTPUT)
$(OUTPUT).game: $(OBJ)
	$(CC) $(OBJ) -LlinLib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(OUTPUT).game
sorry:
	@echo Sorry, no mac support :'('

$(OBJPATH)main.o: $(SOURCEPATH)main.cpp
	$(CC) -c $(SOURCEPATH)main.cpp -o $(OBJPATH)main.o
$(OBJPATH)settings.o: $(SOURCEPATH)settings.cpp
	$(CC) -c $(SOURCEPATH)settings.cpp -o $(OBJPATH)settings.o
$(OBJPATH)gui.o: $(SOURCEPATH)gui.cpp
	$(CC) -c $(SOURCEPATH)gui.cpp -o $(OBJPATH)gui.o
$(OBJPATH)gameScreens.o: $(SOURCEPATH)gameScreens.cpp
	$(CC) -c $(SOURCEPATH)gameScreens.cpp -o $(OBJPATH)gameScreens.o