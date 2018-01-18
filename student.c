# include "student.h"
# include "static_datas.h"
# include "file_utils.h"
# include <conio.h>
# include <string.h>


void exit_on_null(FILE *f);
void input_id(long *id);
void input_name(char name[]);
void input_gender(char gender[]);
void input_age(int *age);
void input_score(char subject[], float *score);
static long file_size;
static int count;
static FILE *src;
static int stu_size;

void init_data_base(){
	src = fopen(DATA_BASE_PATH, "ab+");
	exit_on_null(src);
	file_size = fsize(src);
	stu_size = sizeof(Student);
	count = file_size / stu_size;
}

void add_new_student(){
	Student stud;
	input_name(stud.name);
	input_gender(stud.gender);
	input_id(&stud.id);
	input_age(&stud.age);
	input_score("Chinese", &stud.Chinese);
	input_score("Maths", &stud.Maths);
	input_score("English", &stud.English);
	fseek(src, 0, SEEK_END);
	fwrite(&stud, stu_size, 1, src);
	fflush(src);
}

void show_all_data(){
	Student stud;
	int cnt=0;
	printf("Iterating Data Base:\n");
	printf("Name\tID\tAge\tGender\tChinese\tMaths\tEnglish\tTotal\n");
	float total;
	fseek(src, 0, SEEK_SET);
	while (fread(&stud, stu_size, 1, src)>0)
	{
		total = stud.Chinese + stud.Maths + stud.English;
		printf("%s\t%d\t%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n", stud.name, stud.id, stud.age,stud.gender, stud.Chinese, stud.Maths, stud.English, total);
		cnt++;
	}
	printf("Students Count: %d.\n", cnt);
}

Student *get_stud(int id){
	fseek(src, 0, SEEK_SET);
	static Student stdu;
	while (fread(&stdu,stu_size,1,src)>0)
	{
		if (stdu.id == id){
			return &stdu;
		}
	}
	return NULL;
}

int edit_stud(Student **p){
	Student stdu = **p;
	input_name(stdu.name);
	input_gender(stdu.gender);
	input_age(&stdu.age);
	input_score("Chinese", &stdu.Chinese);
	input_score("Maths", &stdu.Maths);
	input_score("English", &stdu.English);
	printf("Confirm change? y/n\n");
	fflush(stdin);
	char input = _getch();
	if (input == 'y'){
		fseek(src, 0, SEEK_SET);
		int cnt = 0;
		Student temp;
		while (fread(&temp,stu_size,1,src)>0)
		{
			if (temp.id == stdu.id){
				printf("find student!\n");
				printf("New name is %s\n", stdu.name);
				freplace(DATA_BASE_PATH, src, cnt*stu_size, (char*)&stdu, stu_size);
				*p = &stdu;
				return 1;
			}
			else{
               cnt++;
			}
		}
	}
	else{
		printf("Abort changes.\n");
	}
	return -1;

}

static void exit_on_null(FILE *f){
	if (f == NULL){
		printf("Fail to create/open target file :%s, press any key to quit.\n", DATA_BASE_PATH);
		_getche();
		exit(0);
	}
}

static void input_name(char name[]){
	printf("Please enter name(max len <20):");
	fflush(stdin);
	scanf("%s", name);
	if (strlen(name) >= 20){
		printf("Length exceeds maximum, please retry:\n");
		input_name(name);
	}
}

static void input_gender(char gender[]){
	printf("Please enter gender(male/female):");
	fflush(stdin);
	scanf("%s", gender);
	if (strcmp(gender, "female") != 0 && strcmp(gender, "male") != 0){
		printf("Only male or female is selectable!\n");
		input_gender(gender);
	}
}


static void input_id(long *id){
	printf("Please enter Id:");
	scanf("%ld", id);
}

static void input_age(int *age){
	printf("Please enter age:");
	int i = 0;
	scanf("%d", &i);
	if (i > MAX_AGE || i < MIN_AGE){
		printf("Age not valid, please try again.\n");
		input_age(age);
	}
	else
	{
		*age = i;
	}
}

static void input_score(char subject[], float *score){
	printf("Please enter the score of %s:", subject);
	scanf("%f", score);
	if (*score > MAX_SCORE || *score < MIN_SCORE){
		printf("Invalid score for %s, please retry!\n",subject);
		input_score(subject, score);
	}

}

void close_data_base(){
	fclose(src);
}



