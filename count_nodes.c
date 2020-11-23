#include "ttt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  init_boards(); // set all the init to -1
  init_board(START_BOARD); // initalize with the START_BOARD
  join_graph(START_BOARD); // make all the boards based on START_BOARD
  int count = 0;
  // brute force methods -- i'm gonna probably make this a recursive search
  int i = 0;
  for (i = 0; i < HSIZE; i++) {
    if (htable[i]->init == 1) {
      count++;
    }
  }
  return count;
}
