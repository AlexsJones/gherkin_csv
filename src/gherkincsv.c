/*
 * =====================================================================================
 *
 *       Filename:  gherkincsv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/07/2014 09:02:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include "feature_reader.h"
#include "csv_writer.h"
void usage() {
  printf("------------gherkin_csv------------\n");
  printf("Converts feature files into csv's  \n");
  printf("--feature demo.feature\n");
  printf("--output directory/to/output/to\n");
  printf("-----------------------------------\n");
  exit(0);
}
int main(int argc, char **argv) {

  int c;
  static struct option longopts[] = {
    {"feature",required_argument,NULL,'f'},
    {"output",required_argument,NULL,'o'}
  };
  char *fep = NULL;
  char *op = NULL;
  while((c = getopt_long(argc,argv,"f:o:",longopts,NULL)) != -1) {
    switch(c) {
      case 'f':
        fep = optarg;
        break;
      case 'o':
        op = optarg;
        break;
      case '?':
        usage();
        break;
    }
  }
  if(!fep || !op) {
    usage();
  }

  feature_obj *fo = feature_reader_create(fep);
  if(!fo) {
    printf("Sorry: unable to create a feature reader object from the file path %s\n",fep);
  }
  char *formatters[2] = { "iPhone","Android"};
  int res = csv_writer(fo,op,formatters,2);
  return 0;
}
