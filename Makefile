
run: build/tetris
	./build/tetris

build/tetris: src/tetris.c src/utils.c src/tetronimo.c src/draw.c src/collision.c nanovg/build/libnanovg.a
	mkdir -p build
	gcc $< -o build/tetris -O3 -Wall -Wno-missing-braces -lnanovg -lGL -lGLU -lm -lGLEW -pthread `pkg-config --libs glfw3` -L ./nanovg/build

nanovg/build/libnanovg.a:
	cd nanovg; premake4 gmake; cd build; make nanovg;

