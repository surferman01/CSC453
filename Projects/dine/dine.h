#ifndef NUM_PHILOSOPHERS
#define NUM_PHILOSOPHERS 4
#endif
#ifndef DAWDLEFACTOR
#define DAWDLEFACTOR 1000
#endif
// eating means the philosopher is eating
#define EATING 0
// thinking means the philosopher is chillin
#define THINKING 1
// changing means the philosopher is waiting to transition
#define CHANGING 2
// for passing which fork was grabbed
#define LEFT 0
#define RIGHT 1
// empty means the hand is empty
#define EMPTY -1

void get_fork(int index, int id, int side);
void put_fork(int index, int id, int side);
void *start(void *arg);
void eat();
void think();
void print_status();

// sem_overview(7)
// int i = *(int *)ptr;
// int pthread_create( pthread_t * thread,
//     pthread_attr_t * attr,
//     void * (*start_routine)(void *),
//     void * arg);

typedef struct {
  int id;     // the id of the philosopher
  int status; // the current status (EATING, CHANGING, THINKING)
  int left;   // will hold the index of the left hand fork or EMPTY
  int right;  // will hold the index of the right hand fork or EMPTY
} Philosopher;

typedef struct {
  int thread_id;
  Philosopher *phil_list;
} ThreadArgs;