all:
	gcc -o prog main.c `sdl2-config --cflags --libs`
	./prog 5
