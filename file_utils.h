# include <stdlib.h>
# include <stdio.h>

#ifndef _FILE_UTILS_
extern long fsize(FILE *f);
extern long finsert(FILE *f, long toIndex, char *data, long data_len);
extern long fdelete(char*file_name, FILE *f, long fromIndex, long data_len);
extern void freplace(char *file_name, FILE *f, long fromIndex, char*data, long data_len);

#define _FILE_UTILS_
#endif