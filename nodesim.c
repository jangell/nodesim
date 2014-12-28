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
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int printgrid();
int gridinit();

int main(int argc, char * argv[])
{
  int * grid = malloc(sizeof(int) * GRIDSIZEX * GRIDSIZEY);
  gridinit(grid, GRIDSIZEX, GRIDSIZEY);
  randomfinder(grid, GRIDSIZEX, GRIDSIZEY, 4, 5, 28, 13);
  //printgrid(grid, GRIDSIZEX, GRIDSIZEY);
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
      int val = *(grid + (j * GRIDSIZEX) + i);
      if(val == 0){
	printf("o");
      }
      else if(val == 1){
	printf(ANSI_COLOR_RED "x" ANSI_COLOR_RESET);
      }
      else if(val == 2){
	printf(ANSI_COLOR_BLUE "@" ANSI_COLOR_RESET);
      }
      else{
	printf("%i\n", val);
	return 1;
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
