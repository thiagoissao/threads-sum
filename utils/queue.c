#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

void create_queue(Queue* queue) {
  queue->end = NULL;
  queue->start = NULL;
}

bool is_empty(Queue* queue) {
  return queue->start == NULL;
}

bool insert_task(Queue* queue, Task task) {
  TaskQueue* tq;

  tq = malloc(sizeof(TaskQueue));

  if (tq == NULL) {
    return false;
  }

  tq->data = task;
  tq->next = NULL;

  if (is_empty(queue)) {
    queue->start = tq;
  }
  else {
    queue->end->next = tq;
  }

  queue->end = tq;
  return true;
}

bool remove_task(Queue* queue, Task* task) {
  TaskQueue* task_queue;

  if (is_empty(queue)) {
    return false;
  }

  task_queue = queue->start;
  *task = task_queue->data;
  queue->start = task_queue->next;

  if (queue->start == NULL) {
    queue->end = NULL;
  }

  free(task_queue);
  return true;
}

void print_queue(Queue* queue) {
  if (is_empty(queue)) {
    printf("A FILA ESTÁ VAZIA\n");
    return;
  }

  printf("TAREFA ATUAL\n- Ação: %c\n- Tempo de espera: %i\n\n",
    queue->start->data.action, queue->start->data.time);
}

int queue_size(Queue* queue) {
  TaskQueue* tq;
  int cont = 0;

  tq = queue->start;
  while (tq != NULL) {
    cont++;
    tq = tq->next;
  }

  return cont;
}