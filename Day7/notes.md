# Day 7 (4/16/2025)

## Dealing w Concurrency

### Problem:

- race conditions
  - situation where the ordering of a series of events affects the correctness of the outcome
- critical section
  - region of program where it cannot be safely interrupted

### Solution

- no 2 processes may simultaneously enter the critial region
- no assumptions may be made about the # or speed of CPUs
- no process outside of CS should run while a process is in its CS
- no process should wait forever in CS

### Approaches

- disable interrupts if in CS
  - works, foolproof
  - gives too much power
- software lock vars

int lock = 0
while (lock) {
    wait...
    lock = 1;
}
leave() {
    lock = 0;
}

- problem: race condition

- strict alternation
  - give access to a specific process when you finish
  - need to know which other processes are waiting for resource

Process A:

for(;;) {
    while (turn == 1) {
        // spin
    }
    critical_stuff();
    turn = 1;
    non_critical();
}

Process B:
for(;;) {
    while (turn == 0) {
        // spin
    }
    critical();
    turn = 0;
    non_critical();
}

- Peterson's Solution (1981)

int turn;
int interested[2];
void enter(int self) {
    int other;
    other = 1 - self;
    interested[self] = 1;
    turn = self;
    while ((turn == self) && interested[other]) {
        // spin
    }
    critical();

}

void leave(int self) {
    interested[self] = 0;
}

- works, doesnt require strict alternation
- still busy waiting

Hardware Lock Variable
- invent TSL (test + set lock)

enter:  tsl r1, lock
        cmp r1, %0
        jne enter
        ret

leave:  mov lock, %0
        ret

- works, fine grained
- requires HW support
- still busywaiting
