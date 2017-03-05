## Tetris

Who doesn't love tetris? <br />
This is a tetris implementation written in C. <br />
It uses [nanovg](https://github.com/memononen/nanovg) for rendering and thus OpenGL. <br />


![Image of the game window](https://raw.githubusercontent.com/leon-vv/tetris/master/tetris.png)

## Usage

Dependencies: premake4, glew, glfw3

```Bash
sudo apt-get install libglew-dev libglfw3-dev premake4
git clone --recursive https://github.com/leon-vv/tetris
make run
```

The time it takes for a tetronimo to move down, is configurable.
Simply pass the amount of seconds a 'step' should take:
```Bash
./build/tetris 1.23
```

## License

GPL3
