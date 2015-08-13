## Tetris

Who doesn't love tetris? <br />
This is a tetris implementation written in C. <br />
It uses [nanovg](https://github.com/memononen/nanovg) for rendering and thus OpenGL. <br />


![Image of the game window](https://raw.githubusercontent.com/leon-vv/tetris/master/tetris.png)

## Usage

```Bash
git clone --recursive https://github.com/leon-vv/tetris
cd tetris/nanovg
premake4 gmake
cd build
make nanovg config=release
cd ../..
make
./build/tetris
```

## License

GPL3
