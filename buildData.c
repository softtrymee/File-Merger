/*
 * Filename: buildData.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function will take in the content of the merged 
 *              (and possibly sorted) input files (sorted in filelines) and
 *              will filter out consecutive duplicated lines.
 * Date: Mar 11 2017
 * Sources of Help: NONE
 */


#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <stdlib.h>

/* Fucntion name: buildData()
 * Function prototype: struct distinctHead buildData
 *                       ( struct fileLines * fileLines, unsigned int flags);
 * Parameters: fileLines - sorted files
 *             flags - all the flags
 * Side effects: none
 * Error conditions:
 *             1. Dynamic memory allocation failure
 * Return value: struct distinctHead containing the head pointer that points 
 *               to the array of distinctLines structs.
 */

struct distinctHead buildData( struct fileLines * filelines,
                                             unsigned int flags ) {
  struct distinctHead dHead;
  dHead.numDistinctLines = 0;
  for (int i = 0; i < filelines->numLines; i++ ) {
    // if dHead is empty, allocate memory for one distinctLines
    if (dHead.numDistinctLines == 0 ) {
      dHead.head = (struct distinctLine *)malloc(sizeof(struct distinctLine));
      // check for malloc error
      if (dHead.head == NULL) {
        dHead.numDistinctLines = 0;
        (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
        return dHead;
      }
      dHead.head[0].line = filelines -> lines[0];
      dHead.head[0].count = 1;
      dHead.numDistinctLines = 1;
    }

    else {
      char * str = filelines->lines[i];
      char * sstr = dHead.head[dHead.numDistinctLines-1].line;
      unsigned int flg = FLAG_I & flags;
      // flag is not set, still case sensitive
      if (flg == 0) {
        // if two strings are duplicate of each other
        if (strncmp(str, sstr, strlen(str)) == 0 && 
                            strlen(str) == strlen(sstr)) {
          dHead.head[dHead.numDistinctLines-1].count ++;
        }
        // if two strings are not duplicate of each other
        else {
          int idx = dHead.numDistinctLines;
          dHead.head = (struct distinctLine*)realloc(dHead.head, 
                                       sizeof(struct distinctLine)*(idx + 1)); 
          // check for malloc error
          if (dHead.head == NULL) {
            dHead.numDistinctLines = 0;
            (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
            return dHead;
          }
          dHead.head[idx].line = str;
          dHead.head[idx].count = 1;
          dHead.numDistinctLines ++;
        }
      }
      // flag is set, case-insensitive
      else {
        // if two strings are duplicate of each other
        if (strncasecmp(str, sstr, strlen(str)) == 0 &&
                    strlen(str) == strlen(sstr)) {
          dHead.head[dHead.numDistinctLines-1].count ++;
        }
        //if two strings are not duplicate of each other
        else {
          int idx = dHead.numDistinctLines;
          dHead.head = (struct distinctLine*)realloc(dHead.head,
                                        sizeof(struct distinctLine) * (idx+1));
          // check for malloc error
          if (dHead.head == NULL) {
            dHead.numDistinctLines = 0;
            (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
            return dHead;
          }
          dHead.head[idx].line = str;
          dHead.head[idx].count = 1;
          dHead.numDistinctLines ++;
        }
      }
    }

  }
  return dHead;
}
