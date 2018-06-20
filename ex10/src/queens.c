#include "queens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * This algorithm allows to find solution with any number of Queens
 * already placed on board, including 0
 * So, we can pass any empty board, and it will solve this
 * But, in additional, we can pass half-solved board, and algorithm will also solve it
 * It is recursive, moving column by column, we mark cells, where we cannot
 * put new queens with 'X', and try to put Queen in every free cell of a column
 * as we change game table every turn, we make an independent snapshot of it
 */
Cell** snapshot(Cell **orig, int size) {
  Cell **ptr = malloc(size * sizeof(Cell*));
  for(int i = 0; i < size; i++) {
    ptr[i] = malloc(size * sizeof(Cell*));
    memcpy(ptr[i], orig[i], size * sizeof(Cell));
  }
  
  return ptr;
}

void printtable(Cell **table, int size) {
  char ch;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
		  ch = table[i][j].figure;
		  if (ch != 'Q' && ch != 'X')
		    ch = ' ';
		  printf("%c ", ch);
		}
	  printf("\n");
	}
}

void place_and_mark(Cell **table, int size, int row, int col) {
  for (int i = 0; i < size; i++) {
    if (table[i][col].figure != 'Q') table[i][col].figure = 'X';
    if (table[row][i].figure != 'Q') table[row][i].figure = 'X';
  }

  if (row >= col) {
    int i = row - col;
    for (int j = 0; j < size - i; j++)
      table[i + j][j].figure = 'X';
  }
  else {
    int j = col - row;
    for (int i = 0; i < size - j; i++)
      table[i][i + j].figure = 'X';
  }
  
  if (col + row < size) {
    int j = col + row;
    for (int i = 0; i <= j; i++)
      table[i][j - i].figure = 'X';
  }
  else {
    int j = row + col - size + 1;
    for(int i = size - 1; i >= j; i--) {
      table[i][size - i + j - 1].figure = 'X';
    }
  }
  
  table[row][col].figure = 'Q';
}

int place_one_more_queen(Cell **table, int size, int queens_left, int cur_column, Cell **orig) {
  if (queens_left == 0)
    return 1;//queens placed, succes
  if (cur_column == size)
    return 0;//no place for last queens
      
  Cell **copy;
  
  for (int i = 0; i < size; i++) {
    if (table[i][cur_column].figure != 'X' && table[i][cur_column].figure != 'Q') {
      copy = snapshot(table, size);     
      place_and_mark(copy, size, i, cur_column);
      if (place_one_more_queen(copy, size, queens_left - 1, cur_column + 1, orig) == 1) {
        orig[i][cur_column].figure = 'Q'; 
        free(copy);
        return 1;
      }
      
      free(copy);
    }
  }
  
  if (place_one_more_queen(table, size, queens_left, cur_column + 1, orig) == 1)//Yes, we really need this call after a loop
    return 1;

  return 0;
}

void place_queens(Cell **table, int size) {
  int queens_to_place = size;
  Cell **copy = snapshot(table, size);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      if (table[i][j].figure == 'Q') {
        place_and_mark(copy, size, i, j);
        queens_to_place -= 1;
      } 
  place_one_more_queen(copy, size, queens_to_place, 0, table);

  printtable(table, size);
}
