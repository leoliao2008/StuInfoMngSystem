# include <stdlib.h>
# include <stdio.h>

#ifndef _STUDENT_
 typedef struct STUDENT
{
	char name[20];
	int age;
	char gender[10];
	long id;
	float Chinese;
	float Maths;
	float English;
 } Student;

extern void init_data_base();
extern void close_data_base();
extern void show_all_data();
extern void add_new_student();
extern Student *get_stud(int id);
extern int edit_stud(Student **p);
#define _STUDENT_
#endif