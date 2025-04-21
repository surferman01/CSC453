# Day 9 (4/21/2025)

## LWP

listi -> list instructions
nexti -> next assembly instruction

info reg -> tells you contents of register


put pointer to lwp in rdi

## Synchronization

Monitor – region of program where only one thread can be active at a time

Pascal stuff:

monitor Producer, Comsumer
    full, empty: conditions;
    count: integer;
    procedure enter()
    begin
        if count = N then
            wait(full)
        enter_item();
        count := count + 1;
        if count = 1 then
            signal(empty)
    end

    procedure remove()
    begin
        if count = 0 then
            wait(empty);
        remove_item()
        count := count - 1;
        if count = N - 1 then
            signal(full);
    end
    count = 0;

end monitor


procedure producer()
begin
    while true do
    begin
        produce();
        ProduceConsume.enter();
    end
end

procedure consumer()
begin
    while true do
    begin
        ProducerConsumer.remove();
        consume()
    end
end

## Message Passing

if you want something, ask for it

primitives
- send(dest, msg)
- recv(src, msg)

considerations
- addressing
  - individual
  - group
- synchronization
  - synced
  - async
- performance
  - transmission time
  - copying
- loss / duplication / error

advantages
- flexible, elegant


#define N 103

void producer() {
    message m;
    thing item;
    while (true) {
        make(item);
        receive(consumer, m);
        build_message(m, item);
        send(consume, m);
    }
}

void consumer() {
    message empty;
    int i;
    for(i = 0; i < N; i++) {
        send(producer, empty);
    }

    while(true) {
        receive(producer, m);
        extract(m, item);
        send(producer, m);
        eat(item);
    }
}

## IPC Problems

- Producer / Consumer (bounded buffer)
- Dining Philosophers
  - deadlock prone bc race condition
- Readers / Writers
  - shared resource (database)
  - set of observers (readers)
    - readers can operate in parallel
  - set of mutators (writers)
    - can work alone
  - goal:
    - maximize parallelism
    - avoid starvation
      - by holding readers when write called?
      - aging function?
