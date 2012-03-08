exe:	*.cpp
	g++ -g *.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx
	
start:
	gedit main.cpp&
	gedit objects.h&
	gedit objects.cpp&

run:
	./a.out

clean:
	rm a.out
