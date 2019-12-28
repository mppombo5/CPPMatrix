# Matrix

My implementation of a [mathematical matrix](https://en.wikipedia.org/wiki/Matrix_(mathematics)), written in C++.

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Standards](#standards)
- [Tools Used](#tools-used)
- [Documentation](#documentation)

## Introduction

I've been using a lot of matrices in my differential equations and discrete math classes, and the most frequent comment from my professors after we do some contrived calculation is, "don't bother with this too much, it can all be done on computers."

Well, I love math and I love a challenge – so I decided to do that myself! My goal with this library is to provide a lightweight interface to create, manipulate, and perform calculations on matrices and vectors for all your C++ linear algebra needs.

## Installation

CPPMatrix requires CMake v3.3.0 or later to build.

Upon cloning this repository, you can simply run the following commands in the repository directory:

```Shell
cmake .
make
```

to make all default targets. You can also run

```Shell
make help
```

to get a list of all targets that can be made.

The main targets of interest compiled by CPPMatrix are the static and shared (also called dynamic) libraries, both named "`CPPMat`" and both with their corresponding suffix. These are the files you will have to add as targets to whatever projects you will use CPPMatrix with. Upon building either or both libraries with `make static` or `make shared`, they will be compiled in the `lib` directory in the source tree.

The header file `CPPMatrix.h`, which includes the interface for all CPPMatrix classes, is located in the `include` directory.

To use the compiled libraries and header file in your program, you will need to add them to your library and include header search paths. You can either keep the header file and libraries where they are or move them around as you please, just make sure that the search paths are correct.

## Standards

- Developed in C++ according to C++14 ISO standard
- [CMake](https://cmake.org/) is used to build, test, and update
  - CMake 3.3.0 or later is required for CPPMatrix
- I use `lowerCamelCase` for variables and functions, and `m_hungarianNaming` for data members.
  - However, I believe formatting semantics come second to making readable code that's easy to use and understand.

## Tools Used

- CPPMatrix was developed using [JetBrains CLion](https://www.jetbrains.com/clion/), which itself uses CMake to build and update the project.
- The documentation is written in [Markdown](https://daringfireball.net/projects/markdown/).
  - I personally use and recommend Yu Zhang's [Markdown All In One](https://marketplace.visualstudio.com/items?itemName=yzhang.markdown-all-in-one) extension for [VSCode](https://code.visualstudio.com/) for writing Markdown – use whatever works best for you!

## Documentation

The documentation for CPPMatrix is split into two parts: one for those who intend to use CPPMatrix in their programs, and one for the actual development process.

- [User documentation](docs/user/README.md)
- [Developer documentation](docs/dev/README.md)
