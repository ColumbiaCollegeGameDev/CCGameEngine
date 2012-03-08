exe:	*.cpp *.c
	g++ -g *.cpp *.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx

run:
	./a.out

clean:
	rm a.out
