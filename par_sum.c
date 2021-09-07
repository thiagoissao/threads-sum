#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

char* path_file;
int n_threads = -1;

int main(int argc, char* argv[]) {

  int opt;
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

  printf("string: %i %s ", n_threads, path_file);
  return 0;
}