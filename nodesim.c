// Jason Angell
// node simulator
// started 12/28/2014
// last edited 12/28/2014

#include <stdio.h>
#include <stdlib.h>
#include "simulations.h"

#define GRIDSIZEX 70
#define GRIDSIZEY 27

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int printgrid();
int gridinit();

int main(int argc, char * argv[])
{
  int * grid = malloc(sizeof(int) * GRIDSIZEX * GRIDSIZEY);
  gridinit(grid, GRIDSIZEX, GRIDSIZEY);
  *(grid + (GRIDSIZEX * 5) + 4) = 1;
  printgrid(grid, GRIDSIZEX, GRIDSIZEY);
  return 0;
}

// initializes a grid to all zero values
int gridinit(int * grid, int sizex, int sizey)
{
  int i, j;
  for(i = 0; i < sizey; i++){
    for(j = 0; j < sizex; j++){
      *(grid + (GRIDSIZEX * i) + j) = 0;
    }
  }
  return 0;
}

int printgrid(int * grid, int sizex, int sizey)
{
  int i, j;
  for(j = 0; j < sizey; j++){
    for(i = 0; i < sizex; i++){
      if(*(grid + (j * GRIDSIZEX) + i) == 0){
	printf("o");
      }
      else{
	printf(ANSI_COLOR_RED "x" ANSI_COLOR_RESET);
      }
      if(i < (sizex - 1)){
	printf("-");
      }
    }
    printf("\n");
    if(j < sizey - 1){
      for(i = 0; i < sizex - 1; i++){
	printf("| ");
      }
      printf("|");
    }
    printf("\n");
  }
  return 0;
}
