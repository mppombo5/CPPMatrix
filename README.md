# Matrix

My implementation of a [mathematical matrix](https://en.wikipedia.org/wiki/Matrix_(mathematics)), written in C++.

## Introduction

I've been using a lot of matrices in my differential equations and discrete math classes, and the most frequent comment from my professors after we do some contrived calculation is, "don't bother with this too much, it can all be done on computers."

Well, I love math and I love a challenge – so I decided to do that myself! My goal with this library is to provide a lightweight interface to create, manipulate, and perform calculations on matrices and vectors for all your C++ linear algebra needs.

## Standards

- Developed in according to C++17 ISO standard
- [CMake](https://cmake.org/) is used to build, test, and update
- I use `lowerCamelCase` for variables and functions, and `m_hungarianNaming` for data members.
  - However, I believe formatting semantics come second to making readable code that's easy to use and understand.
  - Unless your name is Thien, and your sick, twisted mind uses `rEVERSEcAMELcASE`.

## Tools Used

- Matrix was developed using [JetBrains CLion](https://www.jetbrains.com/clion/), which itself uses CMake to build and update the project.
- The documentation is written in [Markdown](https://daringfireball.net/projects/markdown/).
  - I personally use and recommend Yu Zhang's [Markdown All In One](https://marketplace.visualstudio.com/items?itemName=yzhang.markdown-all-in-one) extension for [VSCode](https://code.visualstudio.com/) for writing Markdown – use whatever works best for you!
