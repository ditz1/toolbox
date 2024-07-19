default:
	g++ -o game.exe ../src/main.cpp -I../include/ -L../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -std=c++17

wsl:
	 x86_64-w64-mingw32-gcc -o game.exe ../src/main.c -I../include/ -L../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	del /Q game.exe
	
cleanwsl:
	rm game.exe

