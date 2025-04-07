# Day 3 (4/7/2025)

## Malloc lab stuff

- round up to 16 bytes
- ensure bottom of heap is evenly divisible by 16 bytes

## History of computing

- multiprogramming
- timesharing
  - same as multiprogramming but switch progs after time has elapsed + between jobs

- Unics
  - Small
  - modular
  - written in high level language (BCPL)
    - used subset of BCPL called B
    - later made C

## System Calls

- os is defined by sys calls
  - syscalls = services that system provides
  - performed w privilege typically
- only os can perform write (syscall)

### Sys Call Mechanisms

- place params in known location
- cause interrupt
- place return in known location

## Startup Process

- power on
- find boot media
- copy first section to 0x7c00 and jump
- find rest of OS and jump

## Regaining control (how OS regains control of machine)

- after yielding control, how do we get it back?
- while in supervisor mode:
  - intall ISRs for syscalls and timer
  - request timer interrupt for some time in the future
- Lower privilege to user mode
  - user program does its actions until:
    - a syscall is made
    - timer expire
  - user program cannot change the ISR or timer
- on interrupt
  - program is interrupted
  - control transferred to ISR in supervisor mode

