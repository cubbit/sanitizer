# Simple sanitizer examples

Simple examples that help understand how a sanitizer works and what it does.

Open the source files and uncomment the lines inside the `main()` function 
to test different situations.

You can see the runtime overhead added by sanitizers by looking at the 
disassembled code with `objdump -d a.out`.

Sometimes the compiler optimization masks or unmasks a bug. You can
test it by adding the `-O2` option.

This has been tested using `g++`. 
It should work the same using `clang++`, but the compiler might be more pedantic
and give you errors or warnings.

## Address sanitizer

Build with `-fsanitize=address` to enable the sanitizer.

Add debug symbols `-g` to improve the sanitizer report.

```
g++ sanitizer.cc -fsanitize=address -g
./a.out 300
```

## Undefined behavior sanitizer

Build with `-fsanitize=undefined` to enable the sanitizer.

By default detected undefined behavior only print a message at runtime.
To terminate the program add `-fno-sanitize-recover` at compilation time.

```
g++ ub.cc -fsanitize=undefined -fno-sanitize-recover -g
./a.out 35
```

## Thread sanitizer

Build with `-fsanitize=thread` to enable the sanitizer.

```
g++ thread.cc -fsanitize=thread
./a.out
```
