// Jason Angell
// random algorithm to go from one arbitrary node to another
// does NOT allow touching the same node twice

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "tools.h"

#define GRIDSIZEX sizex
#define GRIDSIZEY sizey
#define ARCSIZEX GRIDSIZEX * 2
#define ARCSIZEY GRIDSIZEY * 2

#define GRIDSPOT(x, y) (grid + (GRIDSIZEX * (y)) + x)
#define ARCSPOT(x, y)  (arcgrid + (ARCSIZEX * (y)) + x)

int randomfinder(int * grid, int * arcgrid, int sizex, int sizey, int startx, int starty, int endx, int endy)
{
  int onx, ony;
  onx = startx;
  ony = starty;
  *GRIDSPOT(endx, endy) = 2;
  srandom(time(NULL));
  int lastx = onx;
  int lasty = ony;
  int killcount = 0;
  int time = 0;
  int moves = 0;
  while(onx != endx || ony != endy){
    // everything happens here
  	// editing the arc grid is frustrating because of all the arithmetic, BUT:
  		// the order is important; the values that are used depend on what operation(s)
  		// have already happened, so be careful with them
    int currand = random()%8;
    if(currand == 0 && onx < sizex - 1){
      if(*GRIDSPOT(onx+1, ony) == 0){
      	onx++;
      	*ARCSPOT(onx-1, ony*2) = 1;
      }
    }
    else if(currand == 1 && onx > 0){
			if(*GRIDSPOT(onx-1, ony) == 0){
				onx--;
				*ARCSPOT(onx, ony*2) = 1;
			}
    }
    else if(currand == 2 && ony < sizey - 1){
    	if(*GRIDSPOT(onx, ony+1) == 0){
    		*ARCSPOT(onx*2, ony*2+1) = 4;
      	ony++;
      }
    }
    else if(currand == 3 && ony > 0){
    	if(*GRIDSPOT(onx, ony-1) == 0){
    		*ARCSPOT(onx*2, ony*2-1) = 4;
      	ony--;
      }
    }
  	// 2 3
    else if(currand == 4 && onx > 0 && ony > 0){
    	int sym = *ARCSPOT(onx*2-1, ony*2-1);
    	if((sym == 0 || sym == 1) && *GRIDSPOT(onx - 1, ony - 1) == 0){
    		if(sym == 0){
      		*ARCSPOT(onx*2-1, ony*2-1) = 2;
      	}
      	else{
      		*ARCSPOT(onx*2-1, ony*2-1) = 3;
      	}
    		onx--;
      	ony--;
    	}
    }
    else if(currand == 5 && onx < sizex - 1 && ony > 0){
    	int sym = *ARCSPOT(onx*2+1, ony*2-1);
    	if((sym == 0 || sym == 2) && *GRIDSPOT(onx + 1, ony - 1) == 0){
      	if(sym == 0){
      		*ARCSPOT(onx*2+1, ony*2-1) = 1;
      	}
      	else{
      		*ARCSPOT(onx*2+1, ony*2-1) = 3;
      	}
      	onx++;
      	ony--;
      }
    }
    else if(currand == 6 && onx > 0 && ony < sizey - 1){
    	int sym = *ARCSPOT(onx*2-1, ony*2+1);
    	if((sym == 0 || sym == 2) && *GRIDSPOT(onx - 1, ony + 1) == 0){
      	if(sym == 0){
      		*ARCSPOT(onx*2-1, ony*2+1) = 1;
      	}
      	else{
      		*ARCSPOT(onx*2-1, ony*2+1) = 3;
      	}
      	onx--;
      	ony++;
      }
    }
    else if(currand == 7 && onx < sizex - 1 && ony < sizey - 1){
    	int sym = *ARCSPOT(onx*2+1, ony*2+1);
    	if((sym == 0 || sym == 1) && *GRIDSPOT(onx + 1, ony + 1) == 0){
      	if(sym == 0){
      		*ARCSPOT(onx*2+1, ony*2+1) = 2;
      	}
      	else{
      		*ARCSPOT(onx*2+1, ony*2+1) = 3;
      	}
      	onx++;
      	ony++;
      }
    }
    time++;
    if(onx == lastx && ony == lasty){
      killcount++;
      if(killcount > 10){
	printf("Starting point: [%i, %i]\n", startx, starty);
	printf("Ending point:   [%i, %i]\n\n", endx, endy);
	printf("Random:\n");
	printf("DNF (terminated at [%i, %i])\n", onx, ony);
	printf("\ttime =  %i\n", time);
	printf("\tmoves = %i\n", moves);
	return 1;
      }
    }
    else{
      killcount = 0;
      lastx = onx;
      lasty = ony;
      moves++;
    }
    *GRIDSPOT(onx, ony) = 1;
    printgrid(grid, arcgrid, sizex, sizey);
    // sleep to make progression visible, using nanosleep
    struct timespec * sleeptime = malloc(sizeof(struct timespec));
    sleeptime->tv_sec = 1;
    sleeptime->tv_nsec = 0000000;
    nanosleep(sleeptime, sleeptime);
  }
  // print stats
  printf("Starting point: [%i, %i]\n", startx, starty);
  printf("Ending point:   [%i, %i]\n\n", endx, endy);
  printf("Random:\n");
  printf("\ttime =  %i\n", time);
  printf("\tmoves = %i\n", moves);
  return 0;
}
