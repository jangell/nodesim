// Jason Angell
// node simulator
// started 12/28/2014
// last edited 12/28/2014

// see end of file for description of grid & arcgrid

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulations.h"

#define GRIDSIZEX 70
#define GRIDSIZEY 27
#define ARCSIZEX GRIDSIZEX * 2
#define ARCSIZEY GRIDSIZEY * 2

#define ANSI_COLOR_RED 		"\x1b[31m" // target node
#define ANSI_COLOR_BLUE   "\x1b[36m" // node path
#define ANSI_COLOR_GREEN 	"\x1b[32m" // djikstra
#define ANSI_COLOR_RESET  "\x1b[0m"

#define ARCGRID(i, j)  (arcgrid + (j * ARCSIZEX) + i)
#define GRID(i, j)     (grid + (j * GRIDSIZEX) + i)

int printgrid();
int gridinit();

int main(int argc, char * argv[])
{
  srandom(time(NULL));
  int * grid = malloc(sizeof(int) * GRIDSIZEX * GRIDSIZEY);
  int * arcgrid = malloc(sizeof(int) * ARCSIZEX * ARCSIZEY);
  gridinit(grid, GRIDSIZEX, GRIDSIZEY);
  gridinit(arcgrid, ARCSIZEX, ARCSIZEY);
  randomfinder(grid, arcgrid, GRIDSIZEX, GRIDSIZEY, 10, 10, 20, 20);
  //printgrid(grid, arcgrid, GRIDSIZEX, GRIDSIZEY);
  return 0;
}

// initializes a grid to all zero values
int gridinit(int * grid, int sizex, int sizey)
{
  int i, j;
  for(i = 0; i < sizey; i++){
    for(j = 0; j < sizex; j++){
      *(GRID(j, i)) = 0; // note that the j, i is because the loop is nested opposite of the lower loop, where it is i, j
    }
  }
  return 0;
}

int printgrid(int * grid, int * arcgrid, int sizex, int sizey)
{
  int i, j, k;
  k = 0;
  for(j = 0; j < GRIDSIZEY; j++){
    for(i = 0; i < GRIDSIZEX; i++){
      int val = *GRID(i, j);
      if(val == 0){
	printf("o");
      }
      else if(val == 1){
	printf(ANSI_COLOR_BLUE "x" ANSI_COLOR_RESET);
      }
      else if(val == 2){
	printf(ANSI_COLOR_RED "@" ANSI_COLOR_RESET);
      }
      else if(val == 3){
      	printf(ANSI_COLOR_GREEN "+" ANSI_COLOR_RESET);
      }
      else{
	printf("%i\n", val);
	return 1;
      }
      if(*ARCGRID(i, k) == 1){
				printf(ANSI_COLOR_BLUE "-" ANSI_COLOR_RESET);
      }
      else if(*ARCGRID(i, k) == 0){
      	printf(" ");
      }
      else{
      	printf("%i", *ARCGRID(i, k));
      }
    }
    k++;
    printf("\n");
    // print arcs based on arcgrid
    for(i = 0; i < ARCSIZEX; i++){
    	if(*ARCGRID(i, k) == 1){
    		printf(ANSI_COLOR_BLUE "/" ANSI_COLOR_RESET);
    	}
    	else if(*ARCGRID(i, k) == 2){
    		printf(ANSI_COLOR_BLUE "\\" ANSI_COLOR_RESET);
    	}
    	else if(*ARCGRID(i, k) == 3){
    		printf(ANSI_COLOR_BLUE "X" ANSI_COLOR_RESET);
    	}
    	else if(*ARCGRID(i, k) == 4){
    		printf(ANSI_COLOR_BLUE "|" ANSI_COLOR_RESET);
    	}
    	else{
    		printf(" ");
    	}
    }
    k++;
    printf("\n");
  }
  return 0;
}

/* grid looks like:

000110
001010
111001
100010
000100

*/

/* arcgrid looks like:

111001000000
203102301120
011000000000
101221231123
111000000000
203100221001

*/
