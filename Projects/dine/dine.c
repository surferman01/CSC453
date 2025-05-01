#include "dine.h"
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// global philosopher list (for printing mainly)
Philosopher phil_list[NUM_PHILOSOPHERS];
pthread_t phil_threads[NUM_PHILOSOPHERS];

// global for how many cycles each philo will do
int cycles = 1;

// lets init some semaphores
// create a semaphore for each fork to ensure
// that only one person can own a fork
sem_t forks[NUM_PHILOSOPHERS];
// semaphore for being able to update your info + print
sem_t update_table_sem;

void dawdle() {
  /*
   * sleep for a random amount of time between 0 and DAWDLEFACTOR
   * milliseconds. This routine is somewhat unreliable, since it
   * doesn’t take into account the possiblity that the nanosleep
   * could be interrupted for some legitimate reason.
   */
  struct timespec tv;
  int msec = (int)((((double)random()) / RAND_MAX) * DAWDLEFACTOR);
  tv.tv_sec = 0;
  tv.tv_nsec = 1000000 * msec;
  if (-1 == nanosleep(&tv, NULL)) {
    perror("nanosleep");
  }
}

void *start(void *arg) {
  // get my id from the create thread arg
  int my_id = *(int *)arg;

  // boolean to know if im odd / even
  int odd = my_id % 2;
  int i;
  for (i = 0; i < cycles; i++) {
    // set initial status to thinking
    // grab the update/print semaphore
    sem_wait(&update_table_sem);
    // set status in global list
    phil_list[my_id].status = THINKING;
    // print while we still have semaphore
    print_status();
    // RELEASE!!!
    sem_post(&update_table_sem);

    // think
    think();
    // now we want to change to eating
    // so make us in the changing state

    sem_wait(&update_table_sem);
    phil_list[my_id].status = CHANGING;
    print_status();
    sem_post(&update_table_sem);


    // we are now going to put our forks down
    if (odd) {
      // if odd, get the right
      if ((my_id + 1) == NUM_PHILOSOPHERS) {
        // wrap if exceeding index lim
        get_fork(0, my_id, RIGHT);
      } else {
        // otherwise just get next
        get_fork(my_id + 1, my_id, RIGHT);
      }
      // then get the left fork
      get_fork(my_id, my_id, LEFT);
    } else {
      // if even, then get left first
      get_fork(my_id, my_id, LEFT);
      // now get right
      if ((my_id + 1) == NUM_PHILOSOPHERS) {
        // wrap if exceeding index lim
        get_fork(0, my_id, RIGHT);
      } else {
        // otherwise just get next
        get_fork(my_id + 1, my_id, RIGHT);
      }
    }

    // at this point, you should have both forks
    // go eat
    sem_wait(&update_table_sem);
    phil_list[my_id].status = EATING;
    print_status();
    sem_post(&update_table_sem);

    eat();

    // now done eating, put the forks down man...

    sem_wait(&update_table_sem);
    phil_list[my_id].status = CHANGING;
    print_status();
    sem_post(&update_table_sem);

    // lets put these forks down
    if (odd) {
      // if odd, put down the right
      if ((my_id + 1) == NUM_PHILOSOPHERS) {
        // wrap if exceeding index lim
        put_fork(0, my_id, RIGHT);
      } else {
        // otherwise just get next
        put_fork(my_id + 1, my_id, RIGHT);
      }
      // then put down the left fork
      put_fork(my_id, my_id, LEFT);
    } else {
      // if even, then put left first
      put_fork(my_id, my_id, LEFT);

      if ((my_id + 1) == NUM_PHILOSOPHERS) {
        // wrap if exceeding index lim
        put_fork(0, my_id, RIGHT);
      } else {
        // otherwise just get next
        put_fork(my_id + 1, my_id, RIGHT);
      }
    }
  }
  // now lettuce think (b4 death)
  sem_wait(&update_table_sem);
  phil_list[my_id].status = THINKING;
  print_status();
  sem_post(&update_table_sem);
  think();


  return NULL;
}

void get_fork(int index, int id, int side) {
  // if i get a fork here and then get stuck waiting to print to the
  // table while another person tries to grab a fork then isnt htat bad?
  // NO! because this guy will see the print first!!
  // wait but could someone who changes state or something print first?
  // no, i dont think so because they don't update that they have a
  // fork until they are about to print it

  // try to get your fork
  sem_wait(&forks[index]);
  // now we have the fork, lets try and print it
  // wait for the update capability first
  sem_wait(&update_table_sem);

  // set which side the fork is on (used in print_status)
  if (side == RIGHT) {
    phil_list[id].right = index;
  } else {
    phil_list[id].left = index;
  }
  // print while we have sem
  print_status();
  // give back the semaphore so others can grab forks
  sem_post(&update_table_sem);
}

void put_fork(int index, int id, int side) {
  // put down the fork first (give up semaphore)
  // try to get access to the update table to print now
  sem_wait(&update_table_sem);

  // set which side the fork is on (used in print_status)
  if (side == RIGHT) {
    phil_list[id].right = EMPTY;
  } else {
    phil_list[id].left = EMPTY;
  }

  print_status();
  // give up the update table semaphore
  sem_post(&update_table_sem);
  sem_post(&forks[index]);
}

void eat() { dawdle(); }

void think() { dawdle(); }

void print_header() {
  int i;
  int j;
  // print the very top of the header
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    printf("|");
    for (j = 0; j < 8 + NUM_PHILOSOPHERS; j++) {
      printf("=");
    }
  }
  printf("|\n");
  
  // calculate the ascii value + print it
  char ascii;
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    ascii = 'A' + i;
    // if the num of philosophers is even, then we are going
    // to need to make the letter identifier offset by 1 to the right
    // it'll look fine i swear!
    if (NUM_PHILOSOPHERS % 2 == 0) {
      printf("|%*s%c%*s",(7 + NUM_PHILOSOPHERS) / 2 + 1, 
        "", ascii, (7 + NUM_PHILOSOPHERS) / 2, "");
    } else {
      // this is better (perfect center fit :D)
      printf("|%*s%c%*s",(7 + NUM_PHILOSOPHERS) / 2, "",
        ascii, (7 + NUM_PHILOSOPHERS) / 2, "");
    }
  }
  printf("|\n");
  // print bottom of header
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    printf("|");
    for (j = 0; j < 8 + NUM_PHILOSOPHERS; j++) {
      printf("=");
    }
  }
  printf("|\n");
}

void print_status() {
  int i;
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    // left/right_fork will be set to the index
    // of the left fork if it is held
    int left_fork = EMPTY;
    int right_fork = EMPTY;
    char status[8] = "       ";

    // if the left hand isn't empty, set the left_fork
    // = the index of the fork held
    if (phil_list[i].left != EMPTY) {
      left_fork = phil_list[i].left;
    }
    // same for right hand
    if (phil_list[i].right != EMPTY) {
      right_fork = phil_list[i].right;
    }
    // now we have the indicies of the forks held
    // by each philosopher (if they are holding one)

    // the status part after the fork list part
    if (phil_list[i].status == EATING) {
      strcpy(status, " Eat   ");
    } else if (phil_list[i].status == THINKING) {
      strcpy(status, " Think ");
    }

    // print the beginning part
    printf("| ");
    int j;
    // iterate and print a '-' unless they have a fork
    // matching the proper index location to print
    for (j = 0; j < NUM_PHILOSOPHERS; j++) {
      if (j == right_fork) {
        printf("%d", right_fork);
        continue;
      }
      if (j == left_fork) {
        printf("%d", left_fork);
        continue;
      }
      printf("-");
    }
    // print their status after the '---xx' part
    printf(status);
  }
  printf("|\n");
}

int main(int argc, char *argv[]) {
  int i;
  int id[NUM_PHILOSOPHERS];
  // init the table updating semaphore
  sem_init(&update_table_sem, 0, 1);

  // parse the args and get the # of cycles
  if (argc > 1) {
    cycles = atoi(argv[1]);
    if (cycles == 0) {
      perror("Use a number >= 1");
      exit(EXIT_FAILURE);
    }
  }

  // future ben here: this is a note im leaving from 
  // when i was thinking this out:

  // here we need to init the philosophers and
  // maybe we should pass an array of Philosophers
  // to each philosopher so that we can have each
  // philosopher print the lines as they individually
  // update their statuses (and they know all the info
  // from their peers to be able to print)

  // init the id list so that we know the right index of our
  // philosophers (and so they they know who they are...)
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    id[i] = i;
  }

  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    // assign philosopher id
    phil_list[i].id = i;
    // changing = default state
    phil_list[i].status = CHANGING;
    phil_list[i].left = EMPTY;
    phil_list[i].right = EMPTY;

    // init a semaphore for each fork
    sem_t temp;
    forks[i] = temp;
    sem_init(&forks[i], 0, 1);
  }

  print_header();

  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    /* pthread create() launches a new thread running the function
     * child(), passes a poitner to the argument in id[i], and 70
     * places a thread identifier in phil_id[i].
     *
     * A note on C: below, I write ”&phil_id[i]” to indicate the
     * address of the i–th element of the array child, but I could
     * just as well used pointer arithmetic and written ”phil_id+i”.
     */
    int res;
    res = pthread_create(&phil_threads[i], NULL, start, (void *)(&id[i]));
    if (-1 == res) {
      fprintf(stderr, "Child %i: %s\n", i, strerror(res));
      exit(EXIT_FAILURE);
    }
  }
  // wait for all the threads (they'll eventually exit right?..)
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(phil_threads[i], NULL);
  }
  // destroy the semaphores (cleanup)
  sem_destroy(&update_table_sem);
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_destroy(&forks[i]);
  }
  int j;
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
      printf("|");
      for (j = 0; j < 8 + NUM_PHILOSOPHERS; j++) {
        printf("=");
      }
    }
    printf("|\n");
  return 0;
}