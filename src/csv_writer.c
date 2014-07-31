/*
 * =====================================================================================
 *
 *       Filename:  csv_writer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/07/2014 10:08:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <jnxc_headers/jnxfile.h>
#include "csv_writer.h"
#define EXT ".csv"
typedef struct csv_obj {
  const char *path;
  char *file_path_name;

  char *feature_title;
}csv_obj;
char *remove_ext (char* mystr, char dot, char sep) {
  char *retstr, *lastdot, *lastsep;
  if (mystr == NULL)

    return NULL;
  if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
    return NULL;

  strcpy (retstr, mystr);
  lastdot = strrchr (retstr, dot);
  lastsep = (sep == 0) ? NULL : strrchr (retstr, sep);

  if (lastdot != NULL) {
    if (lastsep != NULL) {
      if (lastsep < lastdot) {
        *lastdot = '\0';
      }
    } else {
      *lastdot = '\0';
    }
  }
  return retstr;
}
csv_obj *csv_writer_create(feature_obj *fo) {
  csv_obj *co = malloc(sizeof(csv_obj));
  char *fpath_raw = remove_ext((char*)fo->fpath,'.','/');
  //default the extension to csv?
  size_t len = strlen(fpath_raw) + strlen(EXT) + 1;
  char *fpath_final = malloc(len);
  bzero(fpath_final,len);
  strcpy(fpath_final,fpath_raw);
  strcat(fpath_final,EXT);
  free(fpath_raw);
  co->file_path_name = fpath_final;
  JNX_LOGC(JLOG_NORMAL,"Setting new name as -> %s\n",co->file_path_name);
  return co;
}
void csv_writer_destroy(csv_obj **co) {
  free((*co));
  *co = NULL;
}
size_t csv_writer_write(csv_obj *co,char *line) {
  JNX_LOGC(JLOG_NORMAL,"Writing %s to => %s\n",line,co->file_path_name);  
  size_t bw = jnx_file_write((char*)co->file_path_name,line,strlen(line),"a");
  return bw;
}
char *csv_writer_create_formatted_line(const char *format,...) {
  char buffer[1024];
  va_list ap;
  va_start(ap,format);
  vsprintf(buffer,format,ap);
  va_end(ap);
  return strdup(buffer);
}
int csv_writer(feature_obj *fo,char *formatters[],size_t formatterc) {
  JNXCHECK(fo);
  csv_obj *co = csv_writer_create(fo);

  if(jnx_file_exists(co->file_path_name)) {
    JNX_LOGC(JLOG_ALERT,"File already exists -> %s\n",co->file_path_name);
    csv_writer_destroy(&co);
    return 1;
  }
  /*  generate title */
  co->feature_title = csv_writer_create_formatted_line("%s,%s,%s\n",fo->feature_name,formatters[0],formatters[1]);
  csv_writer_write(co,co->feature_title);
  /*  generate scenario body */
  int x;
  for(x=0;x<fo->scenario_count; ++x) {
    scenario_obj *scenario = fo->scenarios->vector[x]->data;
    JNX_LOGC(JLOG_NORMAL,"Current scenario has %zu lines\n",scenario->num_lines);
    void *data;
    //new scenario
    csv_writer_write(co,"----,,\n");
    while((data = jnx_list_remove_front(&scenario->lines)) != NULL) {
      //new line 
      char *formatted_line = csv_writer_create_formatted_line("%s,,\n",data);
      csv_writer_write(co,formatted_line);
      free(formatted_line);
      JNX_LOGC(JLOG_NORMAL,"--%s\n",data);
    }
  }

  csv_writer_destroy(&co);
  return 0;
}
