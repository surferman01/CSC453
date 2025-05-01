/*
 * trivial pt.c is a re–make of asgn1’s fork–testing program
 * done as as demonstration of pthreads.
 *
 * –PLN
 *
 * Requres the pthread library. To compile:
 * gcc –Wall –lpthread –o trivial pt trivial pt.c
 *
 * Revision History: 10
 *
 * $Log: trivial pt.c,v $
 * Revision 1.1 2003–01–28 12:55:00–08 pnico
 * Initial revision
 *
 *
 *
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define NUM_CHILDREN 4
void *child(void *id) {
  /*
   * this function will be executed as the body of each child 30
   * thread. It expects a single parameter that is a pointer
   * to an integer, its ID.
   * The parameter is a void* to comply with the prototype,
   * but we know what’s really in there.
   */
  int whoami = *(int *)id; /* numeric id */
  printf("Child %d (%d): Hello.\n\n", whoami, (int)getpid());
  printf("Child %d (%d): Goodbye.\n\n", whoami, (int)getpid());
  return NULL; /* exits the thread with no final message */
}
int main(int argc, char *argv[]) {
  pid_t ppid;
  int i;
  int id[NUM_CHILDREN];            /* individual identifiers (see below) */
  pthread_t childid[NUM_CHILDREN]; /* ctivations for each child */
  /* initialize the parent process id for later use */
  ppid = getpid();
  /* initialize an array of ID numbers for the children.
   * It would be tempting to just pass the loop index
   * (like we did with trivial), but a pointer is passed
   * to the new thread, not the argument itself. Because
   * the loop index will change, the effect is not what
   * one would hope. 60
   * So, we give each child its own independent ID
   * in the id array.
   */
  for (i = 0; i < NUM_CHILDREN; i++)
    id[i] = i;
  /* Spawn all the children */
  for (i = 0; i < NUM_CHILDREN; i++) {
    /* pthread create() launches a new thread running the function
     * child(), passes a poitner to the argument in id[i], and 70
     * places a thread identifier in childid[i].
     *
     * A note on C: below, I write ”&childid[i]” to indicate the
     * address of the i–th element of the array child, but I could
     * just as well used pointer arithmetic and written ”childid+i”.
     */
    int res;
    res = pthread_create(
        &childid[i], /* where to put the identifier */
        NULL, child,
        /* don’t set any special properties */ /* call the function */
        (void *)(&id[i])                       /* pass the address of id[i] */
    );
    if (-1 == res) { /* there was an error */
      /* report the error condition */
      fprintf(stderr, "Child %i: %s\n", i, strerror(res));
      exit(-1); /* bail out. */
    }
  }
  /* Say hello */
  printf("Parent (%d): Hello.\n\n", (int)ppid);
  /*
   * Now wait for each child thread to finish.
   * Note: Unlike the original trivial, pthread join()
   * requires us to name a specific thread to wait for, thus
   * the children will always join in the same order regardless 100
   * of when they actually terminate.
   */
  for (i = 0; i < NUM_CHILDREN; i++) {
    pthread_join(childid[i], NULL);
    printf("Parent (%d): child %d exited.\n\n", (int)ppid, i);
  }
  /* Say goodbye */ printf("Parent (%d): Goodbye.\n\n", (int)ppid);
  return 0; /* exit successfully */
}