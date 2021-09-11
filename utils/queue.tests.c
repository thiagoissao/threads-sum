#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

int main() {
  Queue* queue = malloc(sizeof(Queue));
  Task* newTask = malloc(sizeof(Task));
  Task task1, task2, task3;

  task1.action = 'a';
  task1.time = 2;

  task2.action = 'b';
  task2.time = 3;

  task3.action = 'c';
  task3.time = 4;

  create_queue(queue);

  insert_task(queue, task1);
  insert_task(queue, task2);
  insert_task(queue, task3);

  printf("TAMANHO DA LISTA: %i\n", queue_size(queue));

  remove_task(queue, newTask);
  remove_task(queue, newTask);
  // remove_task(queue, newTask);

  printf("NOVO TAMANHO DA LISTA: %i\n", queue_size(queue));
  printf("ESTÁ VAZIA: %i\n", is_empty(queue));
  print_queue(queue);

  printf("TAREFA REMOVIDA\n- Ação: %c\n- Tempo de espera: %i\n\n",
    newTask->action, newTask->time);


}