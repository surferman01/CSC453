# Day 5 (4/11/2025)

## Virtual Machines

- let each process believe its completely alone
- VM/370
- OS runs in user mode
  - privileged operation will cause illegal instruction exception
  - OS simulates the operation

## Client / Server

### Policy vs Mechanism

Policy = what you want to happen
Mechanism = how you make it happen

Goal:

- pull policy out to user level
- remaining mechanism
  - microkernel
- communicate via messages

### MACH

Advantage:

- isolation, limited trust

Disadvantage:

- message passing

## MINIX

4 layers:

0. micro-kernel
  - message passing / interrupts
  - clock
  - system
1. Device Tasks
  - disk
  - eth
  - tty
2. System Services
  - FS
  - MM
  - Reincarnation Server (RS)
3. User Processes
  - init (pid 0)

- all communication via messages
- communication only available between adjacent layers
- deeper layers = more privilege

## Threads

- lightweight processes
- multiple independent streams of control sharing a process
- needs stack + registers

Options:

- user level
  - very lightweight
  - no OS support
    - if one thread blocks, then they all block
- Kernel support
  - kernel support
  - more expensive context switching

assumptions
- errno
- forking
  - does it fork all the threads or just the calling thread?
- exiting

## Race Condition

- any situation where interleaving of series of events affects the correctness of the outcome

## Prog 2

- non preemptive user level threads
