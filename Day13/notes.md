# Day 13 (4/30/2025)

## Multiple Resources

- resource trajectories
- multi-resource

Dijkstras Banker Algorithm

keep table
- needs
- held resources
- remaining need

vector
- resources avail

safety:
- pick a process whose whole vector can be satisfied
- pretend it finished / releases resource
- until all finish or stock
- if (finish)
  - safe
- else
  - unsafe

basically:
- we know who needs what, so let processes that are capable of running (aka: their resources required are free) go first
- then they free their resources and get access to more resources than we started
- repeat this cycle and all processes will get access to resources w/o deadlock

## Devices

Disk
- seek time
- rotation time
- need time
- interleaving

Device Controllers
- digital interface w device
- control / status registers

How to interface w dev controller
- MMIO (Memory mapped IO)
  - device controller pretends to be memory
  - pro:
    - easy
  - con:
    - now not all memory is actually free memory space
- IO Ports
  - use special instructions for IO
  - pro:
    - IO / memory are separate
  - con:
    - requires extra instructions

What to say
- write command to control register
- either poll or interrupt
- transfer data
  - programmed IO
    - OS copies data to memory
    - pro:
      - simple
    - con:
      - overhead
  - direct memory access (DMA)
    - let controller write data to memory directly
    - pro:
      - free delivery
    - con:
      - security complexity
