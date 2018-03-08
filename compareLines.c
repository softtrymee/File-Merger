/*
 * Filename: compareLines.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function compares (case_sensitively) two input strings
 *              using strcmp(). This compare routine will be passed to
 *              qsort() when comparing lines for sorting.
 * Date: Mar 11 2017
 * Sources of Help: NONE
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Function name: compareLines()
 * Function prototype: int compareLines( const void * p1, const void * p2);
 * Parameters: p1 - pointr to the first element
 *             p2 - pointer to the second element
 * Side effects: none
 * Error conditons: none
 * Return values: -1 is strcmp() returns negative value; +1 if positive;
 *                otherwise 0.
 */

int compareLines( const void * p1, const void * p2) {
  char ** ptr1 = (char **)p1;
  char ** ptr2 = (char **)p2;
  if (strcmp(*ptr1, *ptr2) == 0) {
    return 0;
  }

  else if (strcmp(*ptr1, *ptr2) < 0) {
    return -1;
  }

  else {
    return 1;
  }
}
