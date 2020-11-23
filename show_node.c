#include "ttt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  init_boards(); // set all the init to -1
  init_board(START_BOARD); // initalize with the START_BOARD
  join_graph(START_BOARD); // make all the boards based on START_BOARD
  int i = 0;
  int board_num = 0; // stores the board number from argv[]  
  for (i = 1; i < argc; i++) { // iterate thru args
    board_num = atoi(argv[i]);
    print_node(htable[board_num]);
  }
  return 0;
}
