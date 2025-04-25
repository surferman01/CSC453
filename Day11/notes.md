# Day 11 (4/25/2025)

## Dining Philosophers

- mostly match the output...
- forks are ascii values
- 0-9, ;, :.....

## Scheduling

Preemptive
- round robin
- priority scheduling
  - do most important thing
    - hard to manage globally
    - easier w categories

### CTSS

find a spot in the priority queue where the job time takes less than the quantum time

quantum = allocated time for a task

start every level at the shortest quantum
if you use more than that time, move to bigger quantum time
keep doing that until it reaches a quantum where it finishes before quantum ends

idea:
- sort jobs into categories / prioritize interactive jobs
- multiple run queues
- jobs enter @ top queue
- a job that blocks goes to the end (when unblocked)
- job that is preemptive drops a level
- quantum doubles each level
- schedule job from highest priority non-empty queue
- a job attempting IO returns to top level

### Guaranteed / Fair Share

- determine shared based on something
- schedule the job that is owed the most
- keep track of how long each process running

advantages
- fair

disadvantages
- overhead (calculating proc time)
- jobs come and go

### Lottery Scheduling

- simulate fair share
- distribute tickets in proportion to share
- when scheduling, pick ticket @ random

### Minix 2 scheduler

4 layers of process types

0. immediate
1. run to completion
2. run to completion
3. round robin, 1/10s quantum

schedule from lowest-numbered non-empty queue

### Minix 3 scheduler

16 queues
variable quantum

15. idle queue
    - idle

16. user queue
   - init

17. task queue
   - system
   - clock

Rules:
- schedule from lowest # non empty
- process that uses its whole quantum gets another @ end
- process that blocks returns @ head w remaining time
- potential changes
  - a process using whole quantum and is its own successor drops a level
  - whole queue but not own predecessor rises, capped in P.T.

### Final thoughts

different decisions by:
- admission
- memory
- disk
