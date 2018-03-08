/*
 * Filename: main.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: This is the main driver for the program
 * Date: Mar 12 2017
 * Sources of Help: NONE
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/*
 * Function name: main()
 * Fucntion prototype: int main( int argc, char * argv[]);
 * Parameters: 
 *             argc - number of arguments
 *             argv - the list of arguments
 * Side effects: none
 * Error conditions:
 *             1. Bad option detected
 *             2. Mutually exclusive flags set at the same time
 *             3. No files were passed in as command line argument
 *             4. Error detected in sortFiles()
 *             5. Error detected in mergeFiles()
 * Return values:
 *             EXIT_SUCCESS on success; EXIT_FAILURE on failure
 */

int main (int argc, char * argv[] ) {
  
  // if no file passed in, print usage and return
  if (argc == 1) {
    (void)fprintf(stderr, STR_USAGE_SHORT, argv[0], argv[0]);
    return EXIT_FAILURE;
  }
    
  
  int c;
  // build the option struct
  static struct option long_options[] = {
    {FLAG_D_STR, no_argument, NULL, FLAG_D_CHAR },
    {FLAG_U_STR, no_argument, NULL, FLAG_U_CHAR },
    {FLAG_C_STR, no_argument, NULL, FLAG_C_CHAR },
    {FLAG_I_STR, no_argument, NULL, FLAG_I_CHAR },
    {FLAG_R_STR, no_argument, NULL, FLAG_R_CHAR },
    {FLAG_S_STR, no_argument, NULL, FLAG_S_CHAR },
    {FLAG_T_STR, no_argument, NULL, FLAG_T_CHAR },
    {FLAG_H_STR, no_argument, NULL, FLAG_H_CHAR },
    {0, 0, 0, 0}
  };
  unsigned int bitmap = 0; // this will store the bitmap
  int dflg, uflg = 0;  // flags to detect if user entered both
                       // mutually exclusive falgs
  
  int illegal = 0; // indicator for illegal option
  int option_index = 0;
  optind = 1;
  // read all the flags
  while ((c = getopt_long(argc, argv, ARG_STR, long_options, &option_index))
                                                                 != -1){
    switch (c) {
      case FLAG_D_CHAR:
        // if flags was set before
        if (uflg == 1) {
          // print the error message
          (void)fprintf(stderr, STR_ERR_MUTUAL_EX);
          (void)fprintf(stderr, STR_USAGE_SHORT, argv[0], argv[0]);
          return EXIT_FAILURE;
        }
        dflg = 1;
        bitmap = bitmap | FLAG_D; 
        break;

      case FLAG_U_CHAR:
        // if d flag was set before
        if (dflg == 1) {
          (void)fprintf(stderr, STR_ERR_MUTUAL_EX);
          (void)fprintf(stderr, STR_USAGE_SHORT, argv[0], argv[0]);
          return EXIT_FAILURE;
        }
        uflg = 1;
        bitmap = bitmap | FLAG_U;
        break;

      case FLAG_C_CHAR:
        bitmap = bitmap | FLAG_C;
        break;

      case FLAG_I_CHAR:
        bitmap = bitmap | FLAG_I;
        break;

      case FLAG_R_CHAR:
        bitmap = bitmap | FLAG_R;
        break;

      case FLAG_S_CHAR:
        bitmap = bitmap | FLAG_S;
        break;

      case FLAG_T_CHAR:
        bitmap = bitmap | FLAG_T;
        break;
      
      case FLAG_H_CHAR:
        bitmap = bitmap | FLAG_H;
        break;

      default:
        illegal = 1;
        break;
    }  
  }
  // if illegal option was detected, print short usage and return
  if (illegal == 1 && (bitmap & FLAG_H) == 0) {
    (void)fprintf(stdout, STR_USAGE_SHORT, argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  if ((bitmap & FLAG_H)!= 0 ) {
    (void)fprintf(stdout, STR_USAGE_LONG, argv[0]);
    return EXIT_SUCCESS;
  }
  
  int numFiles = argc - optind;
  char * filenames[numFiles];
  // get the filenames from the command line
  for (int i = optind; i <= argc - 1; i++) {
    filenames[i - optind] = argv[i];
  }

  // open all input files passed in and sort the order
  FILE ** file = sortFiles(numFiles, filenames, bitmap);

  // if error occurred in sortFiles, return upon failure
  if (file == NULL)
    return EXIT_FAILURE;
  
  // merge the files
  struct fileLines filelines = mergeFiles(file, numFiles);

  // if error occurred in mergeFiles, return upon failure
  if (filelines.lines == NULL)
    return EXIT_FAILURE;
  // if the s flag was set
  if ((bitmap & FLAG_S) != 0 ) {
    // if the iflag was set as well
    if ((bitmap & FLAG_I) != 0) {
      qsort(filelines.lines, filelines.numLines, sizeof(char *), 
                                                  compareLinesIgnoreCase);     
    }
    // the i flag was not set
    else {
      qsort(filelines.lines, filelines.numLines, sizeof(char *),
                                                   compareLines);
    }
  }

  struct distinctHead dHead = buildData(&filelines, bitmap);
  if (dflg == 1) {
    displayOutput(dHead, bitmap, duplicate);
  }
  else if (uflg == 1) {
    displayOutput(dHead, bitmap, unique);
  }

  else {
    displayOutput(dHead, bitmap, regular);
  }

  for (int j = 0; j < dHead.numDistinctLines; j++) {
    (void)free(dHead.head[j].line);
  }
  (void)free(dHead.head);

  for (int k = 0; k < filelines.numLines; k++) {
    (void)free(filelines.lines[k]);
  }
  (void)free(filelines.lines);

  return EXIT_SUCCESS;
}
