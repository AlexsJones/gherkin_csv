/*
 * =====================================================================================
 *
 *       Filename:  feature_reader.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/07/2014 09:12:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __FEATURE_READER_H__
#define __FEATURE_READER_H__
#include <jnxc_headers/jnxlist.h>

/*
 * Example outputting
 *
 * SCENARIO                 ,IPHONE,ANDROID 
 * Given I am an example
 * When something occurs
 * Then I see a result
 *
 */
typedef struct scenario_obj {
  size_t num_lines;
  jnx_list *lines;  
}scenario_obj;

typedef struct feature_obj {
  size_t scenario_count;
  jnx_list *scenarios;
}feature_obj;

feature_obj* feature_reader_create(const char *fpath);

#endif
