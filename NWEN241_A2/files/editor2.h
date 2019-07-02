 /**
 * editor2.h
 */

#ifndef __EDITOR_H2__
#define __EDITOR_H2__
 
 int editor_count_lines (char *buffer, int BUFFERSIZE);

 int editor_search_multiple (const char *buffer, int BUFFERSIZE, const char *word, int *pos , int  POSSIZE);

 #endif /* __EDITOR_H2__ */
