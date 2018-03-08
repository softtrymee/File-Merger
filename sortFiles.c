/*
 * Filename: sortFiles.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This function will sort the files from filenames using qsort()
 *              and the repective compare functions according to the flags
 *              specified.
 * Date: Mar 06 2017
 * Sources of Help: NONE
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * Function name: sortFiles()
 * Function prototype: FILE ** sortFiles( int numFiles, char * filenames[], 
 *                                       unsigned int flags);
 * Parameters: 
 *            numFiles - number of files
 *            filenames - the array of char* that contains all the file names
 *            flags - all the flags
 * Side effects: none
 * Error conditions:
 *            1. Dynamic memory allocation failure
 *            2. The call to stat() fails 
 *            3. A file fails to open
 * Return values:
 *            Null pointer in the case of error; otherwise an array of opened
 *            files.
 */

FILE ** sortFiles( int numFiles, char * filenames[], unsigned int flags) {
  struct fileInfo fileinfo[numFiles]; // the temporary fileInfo struct array;
  struct stat * buf; 
  unsigned int tFlg;
  unsigned int rFlg;
  char * mode = "r";
  // copy info into fileInfo array
  for (int i = 0; i < numFiles; i++) {
    fileinfo[i].filename = filenames[i];
    buf = &(fileinfo[i].statInformation);
    int errflg;
    errflg = stat(filenames[i], buf);
    if (errflg == -1) {
      perror(filenames[i]);
      return NULL;
    }
  }

  // mask out the T flag
  tFlg = flags & FLAG_T;
  // mask out the R flag
  rFlg = flags & FLAG_R;
  
  // if T flag is set
  if (tFlg != 0) {
    // if R flag is also set
    if (rFlg != 0) {
      qsort(&(fileinfo[0]), numFiles, sizeof(struct fileInfo), 
                             revTimeCompare);    
    }

    // R flag is not set
    else {
      qsort(&(fileinfo[0]), numFiles, sizeof(struct fileInfo),
                             timeCompare);
    }
  }


  // if T flag is not set
  if (tFlg == 0) {
    // but R flag is set
    if (rFlg != 0) {
      qsort(&(fileinfo[0]), numFiles, sizeof(struct fileInfo),
                               revFilenameCompare);
    }

    // R flag is not set either
    else {
      qsort(&(fileinfo[0]), numFiles, sizeof(struct fileInfo),
                               filenameCompare);
    }
  }
  
  // allocate memory for FILE * array
  FILE ** filePtr = (FILE**)malloc(numFiles * sizeof(FILE *));
  
  // check if allocation went well
  if (filePtr == NULL) {
    (void)fprintf(stderr, STR_ERR_MEM_EXCEEDED); 
    return NULL;
  }
  
  // open each file
  for (int i = 0; i < numFiles; i++ ) {
    errno = 0;
    filePtr[i] = fopen(fileinfo[i].filename, mode);
    if (errno != 0 ) {
      perror(fileinfo[i].filename);
      return NULL;
    }
  }

  return filePtr;
}
