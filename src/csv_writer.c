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
#include <string.h>
#include <jnxc_headers/jnxfile.h>
#include "csv_writer.h"

typedef struct csv_obj {
  const char *path;
  char *fname;
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
csv_obj *csv_writer_create(feature_obj *fo,const char *opath) {
  csv_obj *co = malloc(sizeof(csv_obj));
  co->path = opath;
  char *fpath_raw = remove_ext((char*)fo->fpath,'.','/');
  //default the extension to csv?
  size_t len = strlen(fpath_raw) + strlen(".csv") + 1;
  char *fpath_final = malloc(len);
  bzero(fpath_final,len);
  strcpy(fpath_final,fpath_raw);
  strcat(fpath_final,".csv");
  free(fpath_raw);
  co->fname = fpath_final;
  JNX_LOGC(JLOG_NORMAL,"Setting new name as -> %s\n",co->fname);
  return co;
}
void csv_writer_destroy(csv_obj **co) {
  free((*co));
  *co = NULL;
}
int csv_writer_write(csv_obj *co,char *line) {

  return 0;
}
char *csv_writer_create_formatted_line(const char *format,...) {

  return NULL;
}
int csv_writer(feature_obj *fo, const char *opath,char *formatters[],size_t formatterc) {
  csv_obj *co = csv_writer_create(fo,opath);

  if(jnx_file_exists(co->fname)) {
    JNX_LOGC(JLOG_ALERT,"File already exists -> %s\n",co->fname);
    csv_writer_destroy(&co);
    return 1;
  }

  csv_writer_destroy(&co);
  return 0;
}
