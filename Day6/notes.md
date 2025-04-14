# Day 6 (4/14/2025)

## Threads

lwp_create()
lwp_start()
- transfer control from 
lwp_yield()
- yield control to another thread
- use scheduler to choose next thread
lwp_exit()
- terminate thread
lwp_wait()

- Each thread needs its own register file + stack
- mmap to create memory

### State

- registers
- stack

### Changing States

- swap_rfiles()
  - swap registers (using assembly)
- wait waits for another thread to terminate

### Recall

- stacks grow upside down

## Registers

RAX
RBX
RCX
RDX
RS1
RD1
RBP -> base pointer (of current call frame)
RSP -> stack pointer

## Calling Convention

before the call
- put params in known location

call
- push return addr
- transfer control

after call
- setup frame

before return

## Proj 2 needs to be down w x86

- use rosetta for mac?
