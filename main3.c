#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_ITER 30
#define MAX_SLEEP 10

int main() {
  pid_t child1, child2;

  srandom(time(NULL));

  child1 = fork();
  if (child1 < 0) {
      perror("Fork failed for child 1");
      exit(1);
  }

  if (child1 == 0) {
      int iterations = random() % MAX_ITER + 1;
      int i;
      for (i = 0; i < iterations; i++) {
          printf("Child Pid: %d is going to sleep!\n", getpid());
          int sleep_time = random() % MAX_SLEEP + 1;
          sleep(sleep_time);
          printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
      }
      exit(0);
  }

  child2 = fork();
  if (child2 < 0) {
      perror("Fork failed for child 2");
      exit(1);
  }

  if (child2 == 0) {
      int iterations = random() % MAX_ITER + 1;
      int i;
      for (i = 0; i < iterations; i++) {
          printf("Child Pid: %d is going to sleep!\n", getpid());
          int sleep_time = random() % MAX_SLEEP + 1;
          sleep(sleep_time);
          printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
      }
      exit(0);
  }

  int status;
  pid_t terminated_pid;

  terminated_pid = wait(&status);
  printf("Child Pid: %d has completed\n", terminated_pid);

  terminated_pid = wait(&status);
  printf("Child Pid: %d has completed\n", terminated_pid);

  return 0;
}