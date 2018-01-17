# include <stdlib.h>
# include <stdio.h>

#ifndef _FILE_UTILS_
long fsize(FILE *f);
long finsert(FILE *f, long toIndex, char *data, long data_len);
long fdelete(char*file_name, FILE *f, long fromIndex, long data_len);

#define _FILE_UTILS_
#endif