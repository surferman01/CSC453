# Day 12 (4/28/2025)

## I/O

### Devices

Types:

Block (disk)

- I/O typically done in blocks
- seekable

Character (tty)
- I/O done a character @ a time
- not seekable

Preemptable
- CAN be taken from a process w/o harm

Non-preemptable
- CANNOT be taken from process w/o harm
- to use one:
  - request it
  - wait for it to be granted
  - use it
  - release it

### Deadlock

Conditions for deadlock:

1. mutual exclusion
2. hold / wait
3. no preemptive
4. circular wait

Avoidance

- detection / recovery
  - algorithmically
    - detect / break
  - heuristically

- prevention
  - make it impossible to deadlock

- avoidance
  - dont deadlock

hold / wait

- require processes to request all resources @ once
- no deadlock
- inefficient / overly conservative
- mod:
  - require process to drop everything to make another request

Circular Wait

- order resources
- require processes to take them in order
  - order depends on contention of resource
  - more popular resources are 'higher numbered'

- works
- conservative requests
- inefficient use
- mod:
  - allow process to release a higher numbered resource to request a lower numbered one
  - "take locks in order and release in reverse order"

### Dijkstra's Banker's Algorithm

- treat resources like line of credit
- for each, track:
  - max needs
  - current holdings
  - remaining need
- only grant a request if safe to do so

Determining safety:
- pick a satisfiable process
- pretend it finished / release its resources
- if all finish
  - safe, grant request
- else
  - unsafe, dont grant request
