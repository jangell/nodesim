// Jason Angell
// random algorithm to go from one arbitrary node to another
// does NOT allow touching the same node twice

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "tools.h"

#define gridspot (grid + (sizex * ony) + onx)

int randomfinder(int * grid, int sizex, int sizey, int startx, int starty, int endx, int endy)
{
  int onx, ony;
  onx = startx;
  ony = starty;
  *(grid + (sizex * endy) + endx) = 2;
  srandom(time(NULL));
  int lastx = onx;
  int lasty = ony;
  int killcount = 0;
  while(onx != endx || ony != endy){
    // everything happens here
    int currand = random()%4;
    if(currand == 0 && onx < sizex - 1){
      onx++;
      if(*gridspot == 1){
	onx--;
      }
    }
    else if(currand == 1 && onx > 0){
      onx--;
      if(*gridspot == 1){
	onx++;
      }
    }
    else if(currand == 2 && ony < sizey - 1){
      ony++;
      if(*gridspot == 1){
	ony--;
      }
    }
    else if(currand == 3 && ony > 0){
      ony--;
      if(*gridspot == 1){
	ony++;
      }
    }
    if(onx == lastx && ony == lasty){
      killcount++;
      if(killcount > 8){
	printf("Looks like this thing lost the game");
	return 1;
      }
    }
    else{
      killcount = 0;
      lastx = onx;
      lasty = ony;
    }
    *gridspot = 1;
    printgrid(grid, sizex, sizey);
    // sleep to make progression visible, using nanosleep
    struct timespec * sleeptime = malloc(sizeof(struct timespec));
    sleeptime->tv_sec = 0;
    sleeptime->tv_nsec = 50000000;
    nanosleep(sleeptime, sleeptime);
  }
  // print stats
  return 0;
}
