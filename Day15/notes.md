# Day 15 (5/9/2025)

## IO Software

abstraction - hide complexity
organization / standardization
error handling
synchronization

in general

1. interrupt handlers
2. device dependent
3. device independent
4. user programs

user programs
system services
device tasks
kernel / interrupt handler
hardware
physics

## Minix IPC

all messages

synchronous
    send(dest, message)
    recv(src, message)
    send_rec(other, mesage)

asynchronous
    notify(other)

interrupt handlers:

- happen immediately
- do as little as possible + tell someone
- simple: disk interrupt
  - reset device
  - notify disk task
- more complex: just do it
  - ex: clock

## Device Tasks (Device Dependent)

- anything requiring knowledge of the actual device
- generally structured as state machines:

init();
while (1) {
    recv(any, m);
    switch(mm_type) {
        ...
    }
    send(mm_source, reply);
}
cleanup();

### setup + init of driver

DEV_OPEN

- you are trying to be opened
- heres who opened you
- respond OK or not OK
  - 1 or errno number

DEV_GATHER_S

DEV_SCATTER_S

DEV_CLOSE

DEV_IOCTL

- takes fd + number (command) + void ptr
- use to change ownership of a secret (for P4)
  - if not holding secret, let anyone r/w
    - if some r/w let only them r/w

SYS_SIG

CANCEL

HARD_INT

- hardware interrupt sent to driver if it has a HW int
- secret wouldn't have one since theres no HW

## Disk Scheduling

first come first served

- not very efficient cause you might be wasting too much time seeking

shortest seek first

- always go to the shortest path first

elevator algorithm

- do shortest seek first in ONE direction only

## Side Notes

check out: /usr/src/tools for some drivers
make hdboot (build + install kernel)
