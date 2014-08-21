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
    int i;
    for(i=0;i<2;++i) {
      if(strstr(head->_data,action_words[i]) != NULL) {
        switch(i) {
          case FEATURE:
            fo->feature_name = head->_data;
            break;
          case SCENARIO:
            while(head) {
              scenario_obj *so=NULL;
              while(head && !strstr(head->_data,action_words[1])) {
                if(!so) {
                  JNX_LOG(NULL,"Created scenario object\n");
                  so = malloc(sizeof(scenario_obj)); 
                  so->lines = jnx_list_create();
                  so->num_lines = 0;
                }
                JNX_LOG(NULL,"-:%s\n",head->_data);
                if(so) {
                  JNX_LOG(NULL,"Adding lines\n");
                  jnx_list_add(so->lines,head->_data);
                  so->num_lines++;
                }
                head = head->next_node;
              }
              JNX_LOG(NULL,"-------\n");
              if(so) {
                jnx_vector_insert(fo->scenarios,so);
                fo->scenario_count++;
                so = NULL;
              }
              if(head)
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
  jnx_list_destroy(&lines);
}
void feature_reader_destroy(feature_obj **fo) {
  
  free((*fo));
  *fo = NULL;
}
feature_obj* feature_reader_create(const char *fpath) {
  if(!fpath) {
    return NULL;
  }
  char *obuffer;
  size_t br = jnx_file_read((char*)fpath,&obuffer,"r"); 
  if(br == 0) {
    return NULL;
  }

  feature_obj *fo = malloc(sizeof(feature_obj));
  fo->fpath = fpath;
  fo->scenario_count = 0;
  fo->scenarios = jnx_vector_create();

  char *bufferptr = obuffer;
  feature_reader_parse(fo,obuffer,br);
  free(bufferptr);

  JNX_LOG(NULL,"--- Feature Object ---\n");
  JNX_LOG(NULL,"%s\n",fo->feature_name);
  JNX_LOG(NULL,"Scenarios: %d\n",fo->scenario_count);
  JNX_LOG(NULL,"----------------------\n");
  return fo;
}
