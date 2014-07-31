/*
 * =====================================================================================
 *
 *       Filename:  csv_writer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/07/2014 10:01:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __CSV_WRITER_H__
#define __CSV_WRITER_H__
#include "feature_reader.h"
int csv_writer(feature_obj *fo,char *formatters[],size_t formatterc);
#endif
