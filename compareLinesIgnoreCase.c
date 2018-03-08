/*
 * Filename: compareLinesIgnoreCase.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function compares (case-insensitively) two input strings
 *              using strcasecmp(). 
 * Date: Mar 11 2017
 * Sources of Help: NONE
 */


#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Function name: compareLinesIgnoreCase()
 * Function prototype: int compareLinesIgnoreCase( const void *p1, 
 *                                                        const void *p2);
 * Parameters: p1 - pointer to the first element
 *             p2 - pointer to the second element
 * Side effects: none
 * Error condition: none
 * Return values: -1 if strcmp() returns negative value; +1 if positive;
 *                otherwise 0;
 */

int compareLinesIgnoreCase( const void * p1, const void * p2) {
  char ** ptr1 = (char **)p1;
  char ** ptr2 = (char **)p2;
  if (strcasecmp(*ptr1, *ptr2) == 0) {
    return 0;
  }
                            
  else if (strcasecmp(*ptr1, *ptr2) < 0) {
    return -1;
  }
  
  else {
    return 1;
  }
}

