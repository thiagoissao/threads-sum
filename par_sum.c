#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <pthread.h>
#include "./utils/queue.h"

char* path_file;
int n_threads = -1;
pthread_t* workers;

// locks to aggregate variables
pthread_mutex_t sum_mutex;
pthread_mutex_t odd_mutex;
pthread_mutex_t min_mutex;
pthread_mutex_t max_mutex;

// aggregate variables
long sum = 0;
long odd = 0;
long min = INT_MAX;
long max = INT_MIN;
bool done = false;              // this variable will be true if the entire file has been read

Queue* tasks;                   // tasks queue
pthread_cond_t tasks_cv;        // tasks conditional variable
pthread_mutex_t tasks_mutex;    // tasks lock

// update global aggregate variables given a number
void update_global_values(long number)
{
  // simulate computation
  sleep(number);

  // update aggregate variables
  pthread_mutex_lock(&sum_mutex);
  sum += number;
  pthread_mutex_unlock(&sum_mutex);
  if (number % 2 == 1) {
    pthread_mutex_lock(&odd_mutex);
    odd++;
    pthread_mutex_unlock(&odd_mutex);
  }
  if (number < min) {
    pthread_mutex_lock(&min_mutex);
    min = number;
    pthread_mutex_unlock(&min_mutex);
  }
  if (number > max) {
    pthread_mutex_lock(&max_mutex);
    max = number;
    pthread_mutex_unlock(&max_mutex);
  }
}

void* workers_consumers() {
  do
  {
    Task task;
    pthread_mutex_lock(&tasks_mutex);

    while (is_empty(tasks)) {
      printf("done: %i %i\n", !is_empty(tasks), done);
      pthread_cond_wait(&tasks_cv, &tasks_mutex);
    }
    print_queue(tasks);
    remove_task(tasks, &task);
    pthread_mutex_unlock(&tasks_mutex);


    update_global_values(task.time);
  } while (!is_empty(tasks) || !done);

  return NULL;
}

int main(int argc, char* argv[]) {

  int opt;
  char action;  //ação de uma linha do arquivo
  long num;     //tempo de espera de uma linha do arquivo
  FILE* file;

  while ((opt = getopt(argc, argv, "t:f:")) != -1) {
    switch (opt) {
    case 't':
      n_threads = strtoul(optarg, NULL, 0);
      break;
    case 'f':
      path_file = optarg;
      break;
    default:
      printf("“unknown option : %c\n", opt);
    }
  }

  if (n_threads == -1) {
    printf("how to execute: program -t 5 -f ./examples/file.txt \n t => number of threads \n f => path file\n");
    return 0;
  }

  //Memory Allocation for global variables
  pthread_mutex_init(&sum_mutex, NULL);
  pthread_mutex_init(&odd_mutex, NULL);
  pthread_mutex_init(&min_mutex, NULL);
  pthread_mutex_init(&max_mutex, NULL);
  pthread_mutex_init(&tasks_mutex, NULL);
  pthread_cond_init(&tasks_cv, NULL);

  tasks = malloc(sizeof(Queue));
  create_queue(tasks);

  // Criação das threads para os trabalhadores
  workers = malloc(n_threads * sizeof(pthread_t));

  for (int i = 0; i < n_threads; i++) {
    pthread_create(&workers[i], NULL, (void*)workers_consumers, NULL);
  }

  file = fopen(path_file, "r");
  while (fscanf(file, "%c %ld\n", &action, &num) == 2) {
    if (action == 'p') {
      Task task;
      task.action = action;
      task.time = num;

      printf("action time: %li\n", num);
      pthread_mutex_lock(&tasks_mutex);
      insert_task(tasks, task);
      if (!is_empty(tasks)) {
        pthread_cond_broadcast(&tasks_cv);
      }
      pthread_mutex_unlock(&tasks_mutex);
    }
    else if (action == 'e') {
      sleep(num);
    }
    else {
      printf("ERROR: Unrecognized action: '%c'\n", action);
      exit(EXIT_FAILURE);
    }
  }


  // Finish the entire file, set done to true and close the file
  done = true;
  fclose(file);

  for (int i = 0; i < n_threads; i++) {
    pthread_join(workers[i], NULL);
  }

  free(tasks);
  free(workers);

  pthread_mutex_destroy(&sum_mutex);
  pthread_mutex_destroy(&odd_mutex);
  pthread_mutex_destroy(&min_mutex);
  pthread_mutex_destroy(&max_mutex);
  pthread_mutex_destroy(&tasks_mutex);
  pthread_cond_destroy(&tasks_cv);


  printf("%ld %ld %ld %ld\n", sum, odd, min, max);
  return 0;
}