# include "student.h"
# include "static_datas.h"
# include "file_utils.h"
# include <conio.h>
# include <string.h>


void exit_on_null(FILE *f);
void input_id(long *id);
void input_name(char*name);
void input_gender(char*gender);
void input_age(int *age);
void input_score(char *subject, float *score);
static long size;
static int count;
static FILE *src;

void init_data_base(){
	src = fopen(DATA_BASE_PATH, "rb+");
	if (src == NULL){
		src = fopen(DATA_BASE_PATH, "wb+");
	};
	exit_on_null(src);
	size = fsize(src);
	count = size / sizeof(Student);
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
	fwrite(&stud, sizeof(Student), 1, src);
}

void show_all_data(){
	Student stud;
	int cnt=0;
	printf("Iterating Data Base:\n");
	printf("\tName\tID\tGender\tChinese\tMaths\tEnglish\tTotal\n");
	float total;
	while (fread(&stud,sizeof(Student),1,src)>0)
	{
		total = stud.Chinese + stud.Maths + stud.English;
		printf("\t%s\t%d\t%s\t%f.2\t%f.2\t%f.2\t%f.2\n", stud.name, stud.id, stud.gender, stud.Chinese, stud.Maths, stud.English, total);
		cnt++;
	}
	printf("Students Count: %d.\n", cnt);
}

static void exit_on_null(FILE *f){
	if (f == NULL){
		printf("Fail to create/open target file :%s, press any key to quit.\n", DATA_BASE_PATH);
		_getche();
		exit(0);
	}
}

static void input_name(char*name){
	printf("Please enter name(max len <20):");
	char input;
	int count=0;
	while ((input=getchar())>0)
	{
		if (count < 20){
			if (input == '\n'){
				break;
			}
            name[count++] = input;
		}else{
			printf("Length exceeds maximum, please retry:\n");
			input_name(name);
			break;
		}
	}
}

static void input_gender(char*gender){
	printf("Please enter gender(male//female):");
	char *temp = (char*)malloc(sizeof(char)* 20);
	gets(temp);
	if (strcmp(temp, "female") ==0|| strcmp(temp, "male")==0){
		strcat(gender, temp);
		free(temp);
	}else{
		free(temp);
		printf("Only male of female is selectable!\n");
		input_gender(gender);
	}
}

//char name[20];
//int age;
//char gender[10];
//long id;
//float Chinese;
//float Maths;
//float English;

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

static void input_score(char *subject, float *score){
	printf("Please enter the score of %s:", subject);
	float i = 0;
	scanf("%f", &i);
	if (i > MAX_SCORE || i < MIN_SCORE){
		printf("Invalid score for %s, please retry!\n",subject);
		input_score(subject, score);
	}
	else{
		*score = i;
	}

}



