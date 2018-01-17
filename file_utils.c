# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "file_utils.h"

# define SIZE 1024
static void fgen_temp_path(char *path);
static FILE *fnewf(char *path);

long fsize(FILE *f){
	fpos_t p;
	fgetpos(f,&p);
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fsetpos(f, &p);
	return size;
}

long finsert(FILE *f,long toIndex,char *data,long data_len){
	//see if toIndex is within the bound of the file, recorrect if not.
	long size = fsize(f);
	toIndex = max(0, min(toIndex, size));
	//gen temp file
	char temp_path[100] = { '\0' };
	FILE *temp_file = fnewf(temp_path);
	//rewind src file
	fseek(f, 0, SEEK_SET);
	//copy pre-paste part to temp
	char *buffer = (char*)malloc(sizeof(char)*SIZE);
	int n = toIndex / SIZE;
	if (toIndex%SIZE > 0){
		n++;
	}
	int len = 0;
	long copy = 0;
	int gap = 0;
	while (n>0)
	{
		gap = toIndex - copy;
		len = gap > SIZE ? SIZE : gap;
		fread(buffer, 1, len, f);
		copy += fwrite(buffer, 1, len, temp_file);
		n--;
	}
	//copy the paste part to temp;
	fwrite(data, 1, data_len, temp_file);
	//copy the post paste part to temp;
	int cnt = 0;
	while ((cnt = fread(buffer, 1, SIZE, f))>0)
	{
		fwrite(buffer, 1, cnt, temp_file);
	}
	//copy the entire temp file into src file
	fseek(f, 0, SEEK_SET);
	fseek(temp_file, 0, SEEK_SET);
	while ((cnt = fread(buffer, 1, SIZE, temp_file))>0)
	{
		fwrite(buffer, 1, cnt, f);
	}
	free(buffer);
	//set the index of src file to where insert was occured.
	fpos_t  p = toIndex;
	fsetpos(f, &p);
	//delete temp file
	fclose(temp_file);
	remove(temp_path);
	//return the len of insert data
	return copy;
}

long fdelete(char*file_name,FILE *f,long fromIndex,long data_len){
	long dl_cnt=data_len;
	//create temp file
	char temp_path[100] = { '\0' };
	FILE *temp_file = fnewf(temp_path);
	//rewind src file
	fseek(f, 0, SEEK_SET);
	//check and recorrect index and len
	long size = fsize(f);
	fromIndex = max(0, min(fromIndex, size));
	if ((fromIndex + data_len) > size){
		data_len = size - fromIndex;
	}
	//copy the pre-delete section to temp
	char *buffer = (char*)malloc(sizeof(char)*SIZE);
	long copy = 0;
	int n = fromIndex / SIZE;
	if (fromIndex%SIZE > 0){
		n++;
	}
	int gap = 0;
	long len = 0;
	while (n>0)
	{
		gap = fromIndex - copy;
		len = gap > SIZE ? SIZE : gap;
		fread(buffer, 1, len, f);
		copy += fwrite(buffer, 1, len, temp_file);
		n--;
	}
	//copy the post-delete section to temp
	fseek(f, fromIndex+data_len, SEEK_SET);
	int cnt = 0;
	while ((cnt=fread(buffer,1,SIZE,f))>0)
	{
		fwrite(buffer, 1, cnt, temp_file);
	}
	//wipe clear src file
	freopen(file_name, "wb+", f);
	//copy the entire temp file into src file
	fseek(temp_file, 0, SEEK_SET);
	while ((cnt = fread(buffer, 1, SIZE, temp_file))>0)
	{
		fwrite(buffer, 1, cnt, f);
	}
	//set the index of the src file to where delete occured
	fpos_t p = fromIndex;
	fsetpos(f, &p);
	//delete temp file
	fclose(temp_file);
	remove(temp_path);
	free(buffer);
	//return the len of delete data
	return dl_cnt;
}

static void fgen_temp_path(char *path){
	srand((unsigned)time(NULL));
	int r = rand();
	sprintf(path, "temp_file_%d.temp", r*r);
}

static FILE *fnewf(char *path){
	fgen_temp_path(path);
	FILE *f = fopen(path, "wb+");
	return f;
}


//void main(){
//	char path[50] = "temp_file_672313041.temp";
//	FILE *f = fopen(path, "rb+");
//	printf("The size is %ld.\n", fsize(f));
//	char content[] ="This is something I want to insert.";
//	//finsert(f, 500, "This is something I want to insert.", sizeof(content));
//	fdelete(path, f, 0, 50);
//	fclose(f);
//}