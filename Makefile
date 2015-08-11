
nanovg/build/libnanovg.a:
	cd nanovg; premake4 gmake; cd build; make nanovg;

tetris: tetris.c nanovg/build/libnanovg.a
	gcc tetris.c -o tetris nanovg/build/libnanovg.a

