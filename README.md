# Tee (Codeorient test assignment)

## The test assignment text
C++ assignment: tee

The tee command reads its standard input until end-of-file, writing a copy of the input to standard
output and to the file named in its command-line argument. Implement tee using I/O system calls
wrapped in C++ class. By default, tee overwrites any existing file with the given name. In addition,
implement the –a command-line option (tee –a file), which causes tee to append text to the end of a file
if it already exists.

If needed feel free to use any additional 3rd party libraries available for public, as well as a build system
of choice: make, cmake, autotools, etc. Unit tests can be optionally added.

The assignment goal is to test core development skills. Therefore submit as much readable and well-
structured code as possible. Performance speed is a secondary evaluation factor.

## Requirements

* C++17 compatible compiler
* CMake 3.8+

## Usage

`tee [-a] filename`
