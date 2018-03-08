/*
 * Filename: mergeFiles.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function will merge the array of opened files line by
 *              line into a single dynamically allocated lines array.
 * Date: Mar 10 2017
 * Sources of Help: NONE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: mergeFiles()
 * Function prototype: struct fileLines mergeFiles( FILE ** files,
 *                                                        int numFiles );
 * Parameters: files - opened files
 *             numFiles - number of files
 *
 * Side effects: none
 * Error conditions:
 *                1. Dynamic memory allocation fails
 * Return values: 
 *                struct fileLines with lines set to NULL and numLines = -1
 *                if error occured; otherwise return struct fileLines
 */

struct fileLines mergeFiles( FILE ** files, int numFiles) {
  struct fileLines filelines;  // create a struct fileLines
  filelines.numLines = 0;  // initialize numLines counter
  char str[BUFSIZ];
  int cool = 1;
  int readCounter = 0 ;  // the counter counting how many files have been read
  // if the number of read files is less than numfiles, keep looping
  while (cool == 1) {
    
    for (int i = 0; i < numFiles; i++ ) {
      if ( fgets(str, BUFSIZ, files[i]) != NULL ) {

        // if there is nothing in the struct fileLines
        if (filelines.numLines == 0 ) {
          // initialize lines pointer by allocating memory
          filelines.lines = (char**)malloc( sizeof(char*));
          // check for malloc error
          if (filelines.lines == NULL) {
            (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
            filelines.numLines = -1;
            return filelines;
          }  
          // let it point to the line just being read
          int idx = filelines.numLines;
          filelines.lines[idx] = (char*)malloc(sizeof(char) * strlen(str) +1 );
          // check for malloc error
          if (filelines.lines[idx] == NULL) {
            (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
            filelines.lines = NULL;
            filelines.numLines = -1;
            return filelines;
          }
          (void)strcpy(filelines.lines[idx], str); // copy the line
          (filelines.lines[idx])[strlen(str)] = '\0';  // null terminated each line
          filelines.numLines ++; // update line counter
        }
        
        // if this is not the first line to be stored
        else {
          int idx = filelines.numLines;
          // realloc memory, add by one more
          filelines.lines = (char**)realloc(filelines.lines,
                                                 (idx + 1)*sizeof(char*));
          // check for realloc error
          if (filelines.lines == NULL) {
            (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
            filelines.numLines = -1;
            return filelines;
          }

          filelines.lines[idx] = (char*)malloc(sizeof(char) * strlen(str) + 1);
          // check for malloc error
          if (filelines.lines[idx] == NULL) {
            (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED);
            filelines.lines = NULL;
            filelines.numLines = -1;
            return filelines;
          }

          
          // copy the line
          (void)strcpy(filelines.lines[idx], str);
          (filelines.lines[idx])[strlen(str)] = '\0'; // null terminate each line
          filelines.numLines ++; // update line counter
          
        }
      }
      // if the end of this file has been reached
      else {
        // update the counter
        readCounter ++; 
      }
    }
    // if all files have been read
    if (readCounter == numFiles) {
      break;  // break out of the loop
    }
  }
  return filelines;
}
