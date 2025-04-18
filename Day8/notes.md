# Day 8 (4/18/2025)

## LWP

leave
- move bp to sp
- pop bp
ret
- pop rp

## Synchronization

fundamental problem of busywaiting
- must waste time

solution:
- non-busywaiting

sleep()
- go to sleep

wakeup()
- poke a sleeping process / wake it up

#define N 103
int count = 0;

void producer() {
    while(TRUE) {
        produce();
        if (count == N) [
            // if you get interrupted here
            // then both processes will end up
            // asleep w empty buffer
            sleep();
        ]
        enter_item();
        count++;
        if (count == 1) {
            wakeup(consumer);
        }
    }
}

void consumer() {
    while (TRUE) {
        if (count == 0) {
            // if you get interrupted here
            // then the buffer will fill up
            // and both processes will sleep
            sleep();
        }
        remove_item();
        count--;
        if (count == N - 1) {
            wakeup(producer)
        }
        consume();
    }
}

- advantages
  - not busywaiting, finegrained
- disadvantages
  - doesnt work

### Semaphores

- atomic sleep / wakeup

- counter w 2 atomic operations

P(s) = DOWN(s)
if (s > 0) {
    s--;
} else {
    sleep()
}

V(s) = UP(s)
if (sleeping process) {
    wakeup();
} else {
    s++;
}

- utilizes spin lock, but only for short periods

implemented / used 2 ways

- binary semaphore
  - only (0, 1)
- counting semaphore


semaphore mutex = 1;
semaphore full = 0;     // how many elements full
semaphore empty = N;    // default = N (on init)

void producer() {
    while(TRUE) {
        produce();
        DOWN(empty);
        DOWN(mutex);
        enter_item();
        UP(mutex);
        UP(full);
    }
}

void consumer() {
    while (TRUE) {
        DOWN(full);
        DOWN(mutex);
        remove_item();
        UP(mutex);
        UP(empty);
        consume();
    }
}

- remove_item and enter_iterm CANNOT happen simultaneously 

- advantages
  - works
- disadvantages
  - fragile

### Language support

- region of program where only one thread is allowed to be active at a time
- enforced by language
- communicate thru condition vars
  - wait(cond) -> blocks until condition has happened
  - signal(cond)
