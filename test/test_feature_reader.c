/*
 * =====================================================================================
 *
 *       Filename:  test_gherkin_csv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/08/2014 11:52:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <jnxc_headers/jnxcheck.h>
#include "feature_reader.h"
void test_null() {

  feature_obj *fo = feature_reader_create(NULL);
  JNXCHECK(fo == NULL);
}
int main(int argc, char **argv) {

  test_null();
  return 0;
}
