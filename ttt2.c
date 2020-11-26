#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttt.h"

int getMax(int move[9]);
int getMin(int move[9]);

void init_boards() {
  int i = 0;
  for (i = 0; i < HSIZE; i++) {
    htable[i].init = 0;
  }
}

char winner( Board board ) {
  int i = 0;
  int j = 0;
  int k = 0;
  int x_spots[5] = {-1, -1, -1, -1, -1}; // x always starts, therefore, 'X' gets one more turn
  int o_spots[4] = {-1, -1, -1, -1};
  for (i = 0; i < 9; i++) {
    if (board[pos2idx[i]] == 'X') {
      x_spots[j] = i;
      j++;
    } else if (board[pos2idx[i]] == 'O') {
      o_spots[k] = i;
      k++;
    }
  }
  int wscore;
  for (i = 0; i < 8; i++) {
    wscore = 0;
    for (j = 0; j < 3; j++) { // go through each number in the wins array and compare against x_spots
      for (k = 0; k < 5; k++) { // if, in this specific wins case, a value of x_spots matches...
        if (x_spots[k] == WINS[i][j]) {
          wscore++; // add one to this total, which, after going through all 3 numbers, is 3 (ie 3 matches with WINS),
        }
      }
    }
    if (wscore >= 3) {
      return 'X'; // return X
    }
  }
  for (i = 0; i < 8; i++) {
    wscore = 0;
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 4; k++) { // only 4 for 'O'
        if (o_spots[k] == WINS[i][j]) {
          wscore++;
        }
      }
    }
    if (wscore == 3) {
      return 'O';
    }
  }
  // if no player has won outright
  if (depth(board) == 9) {
    return '-'; // returns the tie character
  } else {
    return '?'; // return the in-progress character
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
  int d = depth(board);
  if (winner(board) != '?') {
    return '-';
  } else if (d % 2 == 0) { // x plays on even turns: (0, 2, 4, 6, 8)
    return 'X';
  } else { // o plays on odd turns (1, 3, 5, 7)
    return 'O';
  }
}

void init_board( Board board ) {
  if (board == NULL) {
    fprintf(stderr, "%s\n", "Null board error in init_board");
    exit(-1);
  }
  int bh = board_hash(board);
  htable[bh].init = 1;
  htable[bh].depth = depth(board);
  htable[bh].turn = turn(board);
  htable[bh].winner = winner(board);
  strcpy(htable[bh].board, board);
}

void join_graph( Board board ) {
  if (board == NULL) {
    fprintf(stderr, "%s\n", "Null board error in join_graph");
    exit(-1);
  }
  int i = 0;
  int bh = 0;
  int new_bh = 0;
  for (i = 0; i < 9; i++) {
    bh = board_hash(board);
    if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O') {
      (htable[bh].move)[i] = -1; // This is the recursive base case, stop when board is full for all 8
    } else {
      Board new_board;
      strcpy(new_board, board);
      new_board[pos2idx[i]] = turn(board);
      new_bh = board_hash(new_board);
      // set the move (the edge to the next state) to be the hash of the new board
      (htable[bh].move)[i] = new_bh;
      if (htable[new_bh].init != 1) {
        init_board(new_board);
        join_graph(new_board);
      }
    }
  }
}

void compute_score() {
  int i = HSIZE;
  int d = 9;
  char win;
  for (d = 9; d > -1; d--) {
    for (i = HSIZE; i > -1; i--) {
      if (htable[i].init == 1) {
        if (htable[i].depth == d) {
          win = htable[i].winner;
          if (win == 'X') {
            htable[i].score = 1;
          } else if (win == 'O') {
            htable[i].score = -1;
          } else if (win == '-') {
            htable[i].score = 0;
          } else {
            if ((htable[i].turn) == 'X') {
              htable[i].score = getMax(htable[i].move);
            } else {
              htable[i].score = getMin(htable[i].move);
            }
          }
        }
      }
    }
  }
}

int getMax(int move[9]) {
  int maximum = -1;
  for (int i = 0; i < 9; i++) {
    if (move[i] != -1 && htable[move[i]].init == 1) {
      if (htable[move[i]].score > maximum) {
        maximum = htable[move[i]].score;
      }
    }
  }
  return maximum;
}

int getMin(int move[9]) {
  int minimum = 1;
  for (int i = 0; i < 9; i++) {
    if (move[i] != -1 && htable[move[i]].init == 1) {
      if (htable[move[i]].score < minimum) {
        minimum = htable[move[i]].score;
      }
    }
  }
  return minimum;
}
// int is the index of the board
int best_move( int board ) {
  struct BoardNode node = htable[board];
  int i = 0;
  int sc = 0;
  int valid_sc0 = -1;
  int valid_badmove = 0;
  if (node.turn == 'X') {
    for (i = 0; i < 9; i++) {
      if (node.move[i] > -1) {
        sc = htable[node.move[i]].score;
        if (sc == 1) {
          return i;
        } else if (sc == 0) {
          valid_sc0 = i;
        } else if (sc == -1) {
          valid_badmove = i;
        }
      }
    }
    if (valid_sc0 > -1) {
      return valid_sc0;
    } else {
      return valid_badmove;
    }
  } else {
    for (i = 0; i < 9; i++) {
      if (node.move[i] > -1) {
        sc = htable[node.move[i]].score;
        if (sc == -1) {
          return i;
        } else if (sc == 0) {
          valid_sc0 = i;
        } else if (sc == 1) {
          valid_badmove = i;
        }
      }
    }
    if (valid_sc0 > -1) {
      return valid_sc0;
    } else {
      return valid_badmove;
    }
  }
}
