<<<<<<< HEAD
SRC=src/main.cpp src/gui.cpp src/gameScreens.cpp
=======
SRC=src/main.cpp src/gui.cpp src/gameScreens.cpp src/settings.cpp
>>>>>>> main
OUTPUT=main

win:
	g++ $(SRC) -Llib -lraylib -lgdi32 -lwinmm -o $(OUTPUT)
	./main.exe
linux:
	g++ $(SRC) -LlinLib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(OUTPUT).game
	./main.game