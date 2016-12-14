#ELF Version References

A quick example of how to:

* Export ELF version references in a library
* Select compatible version references when compiling/linking against a library

## Getting Started

Simply run:

`make run`

to make the library and linking program, then run the result.

## Exporting Version References

In the library, the version references can be configured through use of `__asm__(".symver ...")` and a `.map` file.

* `__asm__(".symver <local-symbol>,<global-symbol>@")` creates the `Base` version
* `__asm__(".symver <local-symbol>,<global-symbol>@<version-symbol>")` creates a normal version
* `__asm__(".symver <local-symbol>,<global-symbol>@@<version-symbol>")` creates the default version

The final option with `@@` can only be used once.

The format of the `.map` file is:

```
<version-symbol> {
  global:
    <global-symbol>;
  local:
    <local-symbol>;
} <parent-version-symbol>;
```

When compiled as a shared object with the linker option `--version-script`, only global symbols are exported, and local symbols are hidden. In this way, we can achieve the following list of exported symbols:

```
$ objdump -T libexample.so | grep -i example
libexample.so:     file format elf64-x86-64
0000000000000869 g    DF .text	0000000000000013  EXAMPLE_2.0 example
0000000000000830 g    DF .text	0000000000000013 (Base)       example
0000000000000856 g    DF .text	0000000000000013 (EXAMPLE_1.2) example
0000000000000000 g    DO *ABS*	0000000000000000  EXAMPLE_1.1 EXAMPLE_1.1
0000000000000843 g    DF .text	0000000000000013 (EXAMPLE_1.1) example
0000000000000869 g    DF .text	0000000000000013  Base        example_20
0000000000000000 g    DO *ABS*	0000000000000000  EXAMPLE_1.2 EXAMPLE_1.2
0000000000000000 g    DO *ABS*	0000000000000000  EXAMPLE_2.0 EXAMPLE_2.0
```

The file `example.c` does not contain a function named `example` but rather a series of functions (`example_10`, `example_11`, `example_12` and `example_20`) that are exported as the versioned `example` symbol with different versions.

## Selecting Compatible Version References

Selection of non-default versions of a symbol in a linking program can be achieved also using `__asm__(".symver ...)` but with a different intent. Calling:

`__asm__(".symver <symbol>,<symbol>@<version>")`

will ensure that the linked symbol is the appropriate version from the library. Omitting this or a similar line will cause the linker to simply use the default version as specified by the library.

Based on the existence and content of the `__asm__(".symver ...)` line, we can have the default case, when omitted:

```
$ objdump -p main | grep -i example
  NEEDED               libexample.so
  required from libexample.so:
    0x0541e330 0x00 02 EXAMPLE_2.0
```

```
$ objdump -T main | grep -i example
0000000000000000      DF *UND*	0000000000000000  EXAMPLE_2.0 example
```

the base case, using `__asm__(".symver example,example@")`:

```
$ objdump -p main | grep -i example
  NEEDED               libexample.so
```

```
$ objdump -T main | grep -i example
0000000000000000      DF *UND*	0000000000000000              example
```

or the specified case, using `__asm__(".symver example,example@EXAMPLE_1.1")`:

```
$ objdump -p main | grep -i example
  NEEDED               libexample.so
  required from libexample.so:
    0x0541e631 0x00 03 EXAMPLE_1.1
```

```
$ objdump -T main | grep -i example
0000000000000000      DF *UND*	0000000000000000  EXAMPLE_1.1 example
```
