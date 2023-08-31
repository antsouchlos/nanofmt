# nanofmt

A minimal C++ formatting library resembling `fmtlib`.

## Usage

#### Including in a project

This project's `CMakeLists.txt` provides the `nanofmt` library.
For examples of how to use the library see the `examples` folder. 

#### Building and running the tests

1. Initialize the `googletest` framework submodule
```bash
$ git submodule update --init
```

2. Create the build directory and compile the tests
```bash
$ cmake -B build -S . -G Ninja && cmake --build build/
```

3. Run the tests
```bash
$ ctest --test-dir build/
```

## Limitations

For the compile time preprocessing of format strings non-type template
parameters are heavily relied upon, which means C++20 is required.

Only a limited subset of the `fmtlib` syntax is recognized:
  * Integer formatting in decimal, binary and hexadecimal
  * Float formatting in decimal

Because this library is meant to be used in embedded systems, the design choice
has been made to not use any dynamic memory allocation.
This means, however, that no dynamic width can be implemented;
the number of characters used to represent an element is fixed at compile-time.

There is also no guarantee on the accuracy of serialized floats.
