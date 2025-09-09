SRC=src/main.cpp src/gui.cpp src/gamescreens.cpp
OUTPUT=main

win:
	gcc $(SRC) -Llib -lraylib -lgdi32 -lwinmm -o $(OUTPUT)
	./main.exe
linux:
	g++ $(SRC) -LlinLib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(OUTPUT).game
	./main.game