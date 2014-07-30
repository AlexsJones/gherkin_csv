/*
 * =====================================================================================
 *
 *       Filename:  feature_reader.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/07/2014 09:25:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "feature_reader.h"
#include <ctype.h>
#include <stdio.h>
#include <jnxc_headers/jnxfile.h>

typedef enum e_action {
  FEATURE,
  SCENARIO,
  SCENARIO_OUTLINE,
  STEP
}e_action;

char *trim(char *str)
{
  size_t len = 0;
  char *frontp = str - 1;
  char *endp = NULL;

  if( str == NULL )
    return NULL;

  if( str[0] == '\0' )
    return str;

  len = strlen(str);
  endp = str + len;

  while( isspace(*(++frontp)) );
  while( isspace(*(--endp)) && endp != frontp );

  if( str + len - 1 != endp )
    *(endp + 1) = '\0';
  else if( frontp != str &&  endp == frontp )
    *str = '\0';

  endp = str;
  if( frontp != str )
  {
    while( *frontp ) *endp++ = *frontp++;
    *endp = '\0';
  }
  return str;
}
void feature_reader_process_line(char *line, feature_obj *fo) {
  const char *action_words[3] = {"Feature", "Scenario","Scenario Outline"};
  int i;
  for(i=0;i<3;++i) {
    if(strstr(line,action_words[i]) != NULL) {
      switch(i) {
        case FEATURE:
          fo->feature_name = line; 
          printf("%s\n",fo->feature_name);
          break;
        case SCENARIO:

          break;
      }
    }else {

    }
  }
}
void feature_reader_parse(feature_obj *fo,char *buffer, size_t bs) {

  while(*buffer != '\0') {
    int line_count =0;
    while(*buffer != '\n') {
      ++line_count;
      buffer++;
    }
    char *offset = buffer - line_count;
    if(line_count > 0) {
      char *line = malloc((sizeof(line_count) * sizeof(char)) + sizeof(char));
      bzero(line,(sizeof(line_count) *sizeof(char)) + sizeof(char));
      memcpy(line,offset,line_count);

      char *trimmed_line = strdup(trim(line));
      free(line);
      printf("=>%s\n",trimmed_line);
      feature_reader_process_line(trimmed_line,fo); 
    }
    buffer++;
  }
}
feature_obj* feature_reader_create(const char *fpath) {

  char *obuffer;
  size_t br = jnx_file_read((char*)fpath,&obuffer,"r"); 
  if(br == 0) {
    return NULL;
  }

  feature_obj *fo = malloc(sizeof(feature_obj));
  char *bufferptr = obuffer;
  feature_reader_parse(fo,obuffer,br);

  free(bufferptr);
  return NULL;
}
