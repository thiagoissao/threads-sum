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
Queue* tasks;           // fila de tarefas
pthread_t* master, * workers;

void* master_production() {
  printf("mestre\n");
  return NULL;
}

void* workers_consumers() {
  printf("trabalhadores\n");
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

  tasks = malloc(sizeof(Queue));
  create_queue(tasks);

  // leitura do arquivo e inserção na fila de tafefas
  file = fopen(path_file, "r");
  while (fscanf(file, "%c %ld\n", &action, &num) == 2) {
    if (action == 'p' || action == 'e') {
      Task task;
      task.action = action;
      task.time = num;
      insert_task(tasks, task);

    }
    else {
      printf("ERROR: Unrecognized action: '%c'\n", action);
      exit(EXIT_FAILURE);
    }
  }
  fclose(file);

  // Criação das threads para o mestre e para os trabalhadores
  master = malloc(sizeof(pthread_t));
  workers = malloc(n_threads * sizeof(pthread_t));

  pthread_create(master, NULL, (void*)master_production, NULL);

  for (int i = 0; i < n_threads; i++) {
    pthread_create(&workers[i], NULL, (void*)workers_consumers, NULL);
  }

  pthread_join(*master, NULL);

  for (int i = 0; i < n_threads; i++) {
    pthread_join(workers[i], NULL);
  }


  printf("SIZEOF: %i\n", queue_size(tasks));
  print_queue(tasks);

  free(tasks);
  free(workers);
  free(master);

  return 0;
}