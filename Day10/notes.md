# Day 10 (4/23/2025)

## LWP

- check if swap schedule is pointing to the same scheduler

## Scheduler

### Process States

Running
Blocked
ReadyCreate
Exit

### Process Types

IO-Bound
- short bursts of computation w break for IO

Compute-Bound
- long bursts of computation

### When 2 Schedule

Mandatory
- process exits
- process blocks

Desireable
- creation
- IO interrupt
- timer interrupt

### Evolution Criteria

Fairness
Efficiency/Utilization
Response Time
Turnaround TIme
Throughput

## Non-preemptive / Run to completion

1. first come first served
2. shortest job first
  - optimal for turnaround time
  - how do you estimate compute time
    - you cant
  - starvation (long tasks never happen)

Preemptive
- Round Robin
  - one list
  - a process runs for a quantum, then interrupted and set to end of list
  - utilizaiton / response time determined by quantum
