# System-Monitor

# Introduction

This project predominantly invloves the use of C++ OOP to code a Linux system monitor with similar functionality to the widely
used htop application. This project provides more familiarity the Linux operating system, and also give you insights into how a collection of objects can function together in C++ to form an exciting and complete application!

![System Monitor](images/monitor.png)

## Programming Libraries
The project uses two programming libraries: 

### ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

 Install ncurses within in your Linux environment using : `sudo apt install libncurses5-dev libncursesw5-dev`

### Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository:
```
https://github.com/SreeramVipparla/CppND-System-Monitor.git
``` 
2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

4. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.

