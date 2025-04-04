# Day 2 (4/4/2025)

## Malloc

- any memory address must be divisible by 16
- round buffer sizes to multiple of 16
- can hold ANY mem addr (in <stdint.h>)
  - int ptr_t 
  - uintptr_t 

gcc -o test testprog.o -L . -l malloc

## Test Scripts

- on server: ~pn.cs453/demos/tryAsgn1
- (!pn-cs453/lib/asgn1/test1.b)

## Libraries

- collection of precompiled code
- types:
  - static (archive)
    - lib[name].a
  - dynamic (shared objects)
    - lib[name].so (.dylib for macs)

## Compiling

- hello.c
- compile
- hello.o
- linker
- a.out
- loader
- ld.so -> gathers other .so libraries
- running

- gcc
- -c = compile only
- -I = add a directory for includes
- -E = preprocessor only
- -S = emit assembly

## Linking

- -L where to look for libraries
- -l [name] = look for lib[name]

- Linking done in order
- ld.so uses: 
  - LD_LIBRARY_PATH
    - set this to .
    - export LD_LIBRARY_PATH=.
  - LD_PRELOAD

## Makefile

- rules
- this: that
- <tab> -> how to make this out of that

- is this older than that?
  - if yes: run command <tab>