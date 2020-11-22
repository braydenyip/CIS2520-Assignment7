#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttt.h"

void init_boards() {
  int i = 0;
  for (i = 0; i < HSIZE; i++) {
    htable[i]->init = 0;
  }
}

char winner( Board board ) {
  if (depth(board) == 9) { // if all spaces are filled

  }
}

int depth( Board board ) {
  int d, i;
  d = 0;
  if (board == NULL) {
    fprintf(stderr, "%s\n", "Null board error");
    exit(-1);
  }
  for (i = 0; i < BSIZE; i++) {
    if (board[i] == 'X' || board[i] == 'O') {
      d++;
    }
  }
  return d;
}

char turn( Board board ) {

}

void init_board( Board board ) {

}

void join_graph( Board board ) {

}
