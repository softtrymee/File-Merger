/*
 * Filename: displayOutput.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function simply takes the array of distinctLine struct
 *              created in buildData() and displays the output lines according
 *              to the outputMode.
 * Date: Mar 11 2017
 * Sources of Help: NONE
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Function name: displayOutput()
 * Function prototype: void displayOutput( struct distinctHead dHead, 
 *                           unsigned int flags, enum outputMode oMode);
 * Parameters: dHead - the struct
 *             flags - all the flags
 *             oMode - the output mode
 *
 * Side effects: none
 * Error conditions: none
 * Return value: none
 */

void displayOutput( struct distinctHead dHead, unsigned int flags, 
                           enum outputMode oMode) {
  unsigned int cflg = FLAG_C & flags;
  
  for (int i = 0; i < dHead.numDistinctLines; i++) {
    if (oMode == duplicate && cflg != 0) {
      if (dHead.head[i].count > 1) {
        (void)printf(STR_COUNT_PREFIX, dHead.head[i].count);
        (void)printf(" %s", dHead.head[i].line);
      }
    }

    if (oMode == duplicate && cflg == 0) {
      if (dHead.head[i].count > 1) {
        (void)printf("%s", dHead.head[i].line);
      }
    }

    if (oMode == unique && cflg != 0) {
      if (dHead.head[i].count == 1) {
        (void)printf(STR_COUNT_PREFIX, dHead.head[i].count);
        (void)printf(" %s", dHead.head[i].line);
      }
    }

    if (oMode == unique && cflg == 0) {
      if (dHead.head[i].count == 1) {
        (void)printf("%s", dHead.head[i].line);
      }
    }

    if (oMode == regular && cflg != 0) {
      (void)printf(STR_COUNT_PREFIX, dHead.head[i].count);
      (void)printf(" %s", dHead.head[i].line);
    }

    if (oMode == regular && cflg == 0) {
      (void)printf("%s", dHead.head[i].line);
    }
  }
  return;
}
