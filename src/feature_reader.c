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
void feature_reader_process_lines(jnx_list *lines,feature_obj *fo) {
  const char *action_words[3] = {"Feature", "Scenario","Scenario Outline"};

  jnx_node *head = lines->head; 
  while(head) {
    printf("->%s\n",head->_data);
    int i;
    for(i=0;i<2;++i) {
      if(strstr(head->_data,action_words[i]) != NULL) {
        switch(i) {
          case FEATURE:
            break;
          case SCENARIO:
            printf("->\n");
            while(head) {
              if(strstr(head->_data,action_words[i]) != NULL) break;
              printf("- - %s\n",head->_data);
              head = head->next_node;
            }
            break;
        }
      }

    }
    if(head)
    head = head->next_node;
  }
}
void feature_reader_parse(feature_obj *fo,char *buffer, size_t bs) {

  jnx_list *lines = jnx_list_create();

  while(*buffer != '\0') {
    int line_count =0;
    while(*buffer != '\n') {
      ++line_count;
      buffer++;
    }
    char *offset = buffer - line_count;
    if(line_count > 0) {
      char *line = malloc((line_count * sizeof(char)) + sizeof(char));
      bzero(line,(line_count *sizeof(char)) + sizeof(char));
      memcpy(line,offset,line_count * sizeof(char));
      char *trimmed = strdup(trim(line));
      free(line);
      jnx_list_add(lines,trimmed);
    }
    buffer++;
  }
  feature_reader_process_lines(lines,fo);
}
feature_obj* feature_reader_create(const char *fpath) {

  char *obuffer;
  size_t br = jnx_file_read((char*)fpath,&obuffer,"r"); 
  if(br == 0) {
    return NULL;
  }

  feature_obj *fo = malloc(sizeof(feature_obj));
  fo->scenario_count = 0;
  fo->scenarios = jnx_vector_create();

  char *bufferptr = obuffer;
  feature_reader_parse(fo,obuffer,br);

  free(bufferptr);
  return NULL;
}
