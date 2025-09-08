win:
	gcc src/main.cpp src/gameScreens.cpp -Llib -lraylib -lgdi32 -lwinmm -o main
	./main.exe
linux:
	g++ src/main.cpp src/gameScreens.cpp -LlinLib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main.game
	./main.game