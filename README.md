# ArkNix

[![wakatime](https://wakatime.com/badge/user/52b07b43-d885-460d-9f43-aff8564c26f1/project/3f31fdfb-1ee7-47f9-b23f-8e4f16e6c8cd.svg)](https://wakatime.com/badge/user/52b07b43-d885-460d-9f43-aff8564c26f1/project/3f31fdfb-1ee7-47f9-b23f-8e4f16e6c8cd)

This repo contains my Udacity Capstone project, called ArkNix, it is a mix between Galaga and Space Invaders.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing
purposes.

### Cloning

In order to clone this project, be sure to use the --recurse-submodules flag.

``
git clone --recurse-submodules https://github.com/BennyFranco/CppND-Capstone-Galaga.git
``

The project includes the following submodules:

- SDL2
- SDL2_Image
- SDL2_Mixer
- SDL2_ttf
- yaml-cpp

### Prerequisites

- CMake >= 3.20
    - Instructions [here](https://cmake.org/install/)

### Linux

- gcc/g++ >= 7.4.0
    - In Ubuntu, you could install build-essential with `sudo apt install build-essential` command.

### Windows

- Install Visual Studio 2022
    - Ensure you install the c++ support. Check
      this [post](https://devblogs.microsoft.com/cppblog/getting-started-with-visual-studio-for-c-and-cpp-development/)
      about C++ development with vstudio.
    - This project was NOT tested with MinGW in Windows.

### macOS

- Not tested yet.

## Compiling and Running

### Compiling

Follow the next steps to compile this project:

1. Create a folder called `build`:

``` 
mkdir build && cd build
```

2. To compile a debug version, run the following cmake config command:

``` 
cmake .. -DCMAKE_BUILD_TYPE=Debug 
```

3. Build the project with:

``` 
cmake --build .
```

### Running

The executable will be placed inside build directory, run it with the following command:

```
./ArkNix
```

## Troubleshooting

### Renderer Issues

In some Ubuntu versions, I had issues creating the window and the renderer of SDL2, if the game shows the following
error
in the console:

```
[SDLRenderer] Window cannot be created. Error: No available video device
[SDLRenderer] Renderer cannot be created. Error: Parameter 'window' is invalid
```

you will need to install `xorg-dev` with the following command:

```
sudo apt-get install xorg-dev
```

you can find more information about this in the
following [link](https://askubuntu.com/questions/443053/could-not-initialize-sdl-no-available-video-device-dont-move).

### Audio Issues

In some Ubuntu versions, I had issues initializing the audio with SDL_mixer, if the game shows the following message
in the console:

```
[SDLAudio] Cannot be initialized. Error: dsp: No such audio device
```

Please, install `libasound2-dev` and `libpulse-dev` with the following command:

```
sudo apt-get install libasound2-dev libpulse-dev
```

more information about this issue in
this [link](http://forums.libsdl.org/viewtopic.php?t=7609&sid=40fdb9756b8e22e1b8253cda3338845f).