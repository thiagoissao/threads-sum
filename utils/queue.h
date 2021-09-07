#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef QUEUE_H_
#define QUEUE_H_

struct task {
  char action;
  int time;
};

struct tasks_queue {
  struct task data;
  struct tasks_queue* next;
};

typedef struct task Task;

typedef struct tasks_queue TaskQueue;

typedef struct {
  TaskQueue* start;
  TaskQueue* end;
} Queue;

void create_queue(Queue* queue);
bool is_empty(Queue* queue);
bool insert_task(Queue* queue, Task task);
bool remove_task(Queue* queue, Task* task);
void print_queue(Queue* queue) ;
int queue_size(Queue* queue);

#endif