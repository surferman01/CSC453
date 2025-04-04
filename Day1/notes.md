# Day 1 (4/1/2025)

## Scheduler

- round robin scheduler

### States

- running
- ready
- blocked
- terminating

## Lab 1

- execv when exits will exit the whole program
- so fork the process and make a child do it first
- signal(SIGKILL, sh) -> assigns sh function to when SIGKILL is gotten
- kill(pid, signal) -> just sends a signal to a process (may not kill it..)
- raise(SIGSTOP)
- kill(pid, SIGCONT)
- kill(pid, SIGSTOP)