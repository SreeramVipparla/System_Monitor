## System-Monitor Project

<a href="System Monitor" target="_blank">
<img src="https://user-images.githubusercontent.com/86887626/134106616-d0f8c64e-f210-4efe-bc6d-8fbbf207f947.png"  width="300" height="300"/>

## Introduction

In this project I have developed an application similar to HTop. This Project predominantly involves the use of C++ OOP and  provides more familiarity the Linux operating system, and gives the insight into how a collection of objects can function together in C++ to form an exciting and complete application!

![System Monitor](images/monitor.png)

## Programming Libraries
This project uses two programming libraries:
#### 1)ncurses

[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Install ncurses within in your Linux environment using : `sudo apt install libncurses5-dev libncursesw5-dev`

#### 2)Make

This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:

- `build` compiles the source code and generates an executable
- `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
- `debug` compiles the source code and generates an executable, including debugging symbols
- `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository:

```
https://github.com/SreeramVipparla/CppND-System-Monitor.git
```

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
   ![Starting System Monitor](images/starting_monitor.png)

4. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.
