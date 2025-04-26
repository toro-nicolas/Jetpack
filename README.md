# Jetpack

![Jetpack](https://toro-nicolas.github.io/Jetpack/preview2.png)

## Table of contents 📑
- [Description](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#description-)
- [Usage](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#usage-%EF%B8%8F)
- [Result](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#result-)
- [Compilation](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#compilation-%EF%B8%8F)
- [Documentation](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#documentation-)
- [Code mandatory](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#code-mandatory-)
- [Contributors](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#contributors-)


## Description 📝
The **Jetpack** is a project carried out by **groups of 3** (see [Contributors](https://github.com/toro-nicolas/Jetpack/blob/main/README.md#contributors-), during our **2nd year** in [**EPITECH**](https://www.epitech.eu/) Grand Ecole program.  
Its purpose is to recreate in [**C++**](https://en.wikipedia.org/wiki/C%2B%2B) a [**Jetpack Joyride game**](https://en.wikipedia.org/wiki/Jetpack_Joyride) with a **multiplayer** mode.  
We had to create a **server** and a **client** that communicate with each other using the **TCP protocol**.  
The game is a **side-scrolling** runner where the player controls a character that automatically moves forward.  
The player can control the character's vertical position by pressing space key to make it fly and releasing it to let it fall.  
The goal is to collect coins while avoiding obstacles.  


## Usage ⚔️
You can run Jetpack server like this :
```sh
./jetpack_server -p [port] -m [map]
```
For more information, please see the help section.
```sh
> ./jetpack_server --help
USAGE: ./jetpack_server -p <port> -m <map> [-d]

DESCRIPTION:
        -p <port>       The port number on which the server socket listens
        -m <map>        The path of the map file
        -d              Enable debug mode
        -in             Enable infinite mode
        --help          Display this help message

CREDITS:
        Made by Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
        EPITECH Nice 2025
```

You can run Jetpack client like this :
```sh
./jetpack_client -h [host] -p [port]
```
For more information, please see the help section.
```sh
> ./jetpack_client --help
USAGE: ./jetpack_client -h <ip> -p <port> [-d]

DESCRIPTION:
        -h <ip> The server IP address
        -p <port>       The port number on which the server socket listens
        -d              Enable debug mode
        --help          Display this help message

CREDITS:
        Made by Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
        EPITECH Nice 2025
```


## Result 🚩
The result of this project is a **almost perfect Jetpack Joyride game in multiplayer**.  
If you discover a **problem** or an **error**, don't hesitate to **create an issue** and **report it** to us as soon as possible.


### my.epitech.eu result
| Test name                                 |  Result  | Crash  |
|-------------------------------------------|:--------:|:------:|
| Server                                    |    OK    |   No   |
| Client                                    |    OK    |   No   |
| Minimal functions client (write and poll) |    OK    |   No   |
| Minimal functions server (write and poll) |    OK    |   No   |
| Documentation                             |    OK    |   No   |
| **Results**                               | **100%** | **No** |

### Defense
TODO


## Compilation 🛠️
This project is compiled with **CMake** and **Makefile**.  
This project use **C++20** standard, **CMake 3.20** or higher and **SFML 2.5.1**.  

You can compile the project with this command :
- via CMake and Makefile :
```sh
cmake -B build -S . && make -s -C build -j
```
- via only Makefile :
```sh
make
```

If you want to debug the program, you can compile the project with this :
- via CMake and Makefile :
```sh
cmake -B build -S . && make debug -s -C build -j
```
- via only Makefile :
```sh
make debug 
```

If you want clean the project, you can run this command :
- via CMake and Makefile :
```sh
cmake -B build -S . && make fclean -s -C build -j
```
- via only Makefile :
```sh
make fclean
```

You can clean and compile the project with the rules ```re``` and for debugging ```re_debug```


## Documentation 📚
The requested documentation for EPITECH is accessible [here](https://toro-nicolas.github.io/Jetpack/doc.txt).  
The protocol documentation is accessible [here](https://toro-nicolas.github.io/Jetpack/protocol_documentation_en.md).  
The map documentation is accessible [here](https://toro-nicolas.github.io/Jetpack/map_documentation.md).  
The code documentation is accessible [here](https://toro-nicolas.github.io/Jetpack/html/).  

You can generate the documentation with this command :
- via CMake and Makefile:
```sh
cmake -B build -S . && make doc -s -C build -j
```
- via only Makefile:
```sh
make doc
```
You need multiple package for generate them :
- doxygen
- doxygen-latex
- doxygen-doxywizard
- graphviz


## Code mandatory 📦
- You'll need to create a branch where you'll push your code. Once you've completed your tasks on this branch, we'll work together to merge it and check that everything works.
- Every function you add must be code-style and documented.
- If the github actions don't succeed, then ask yourself some questions
- Each commit will contain ```[+]``` or ```[-]``` or ```[~]``` followed by a message
    - ```[+]``` : Add feature
    - ```[-]``` : Delete feature
    - ```[~]``` : Edit feature

**Of course, in exceptional cases, we may depart from these rules.**


## Contributors 👥
For this project, we were a group of **3 people**. Here are the people in the group:
- [Christophe VANDEVOIR](https://github.com/ItsKarmaOff) : also published the [Jetpack](https://github.com/ItsKarmaOff/Jetpack)
- [Guillaume LECOCQ](https://github.com/guilec06)
- [Nicolas TORO](https://github.com/toro-nicolas) : also published the [Jetpack](https://github.com/toro-nicolas/Jetpack)
