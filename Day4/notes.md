# Day 4 (4/9/2025)

## Processes

### Users Perspective

- each process has its own:
  - memory
  - CPU
  - IO channels (file descriptors)
  - identity
- each process is unaware of other processes

### OS Perspective (the context)

what must be maintained?

- processes' resources:
  - registers
  - memory
  - identity
  - signal masks
  - umask
  - file descriptors
- kept in process table
  - process table holds the PC of the process also
- changing processes is a context switch

### Context Switch

- process A interrupted
- save registers
  - push to stack?
    - like push to the stack of the process itself so when context comes back, you fix all the registers before code exec
  - push to heap?
- save SP and switch to kernel stack
- save A's memory
- kernel performs its operations
- choose a process
- load its data
- switch back to B's stack
- restore B's registers
- return from interrupt

## Parallelism

- pseudo-parralellism
  - sharing a single CPU
- true parallelism
  - multiple CPUs

- cannot make any assumptions about timing

## Process States

- running
  - loaded in mem + actively executing instructions on CPU
- ready
  - ready to be running, waiting turn
- blocked
  - unable to run until external event occurs

- state transitions managed by scheduler

## OS Structures

- monolithic system
  - one large object
  - syscall goes to dispatch
    - call other modules
    - utility routines

- advantages
  - efficient
- disadvantages
  - no internal data protection
  - requires disciplined programming
  - hard to maintain
  - errors propagate

### Layered Systems

- series of layers of increasingly powerful abstractions
- THE operating system (Dijkstra)
  - 6 layers
    0. processor allocation / multiprogramming
       - own cpu
    1. memory and drum management
       - own mem
    2. operator-process communication
       - contact operator
    3. abstract IO streams
       - iostreams 
    4. user processes
    5. operator
