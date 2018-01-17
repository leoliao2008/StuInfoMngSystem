# include <stdlib.h>
# include <stdio.h>

#ifndef _STUDENT_
 struct STUDENT
{
	char name[20];
	int age;
	char gender[10];
	long id;
	float Chinese;
	float Maths;
	float English;
 };
 typedef struct STUDENT Student;

void init_data_base();
void show_all_data();
void add_new_student();
#define _STUDENT_
#endif