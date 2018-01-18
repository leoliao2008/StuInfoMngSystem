# include "student.h"
# include <conio.h>
int show_menu();
void edit_stud_menu(int id);
int input_id();

void main(){
	init_data_base();
	while (1)
	{
		switch (show_menu())
		{
		case '1':
			add_new_student();
			break;
		case '2':
			show_all_data();
			break;
		case '3':
			edit_stud_menu(input_id());
			break;
		case '0':
			exit(1);
			break;
		default:
			break;
		}
	}
	close_data_base();
}

int show_menu(){
	printf("---------------------------------------------------------------------------\n");
	printf("-------------------------学生信息管理系统----------------------------------\n");
	printf("---------------------------------------------------------------------------\n");
	printf("--------------1,增加学生                          -------------------------\n");
	printf("--------------2,遍历数据库                        -------------------------\n");
	printf("--------------3,编辑学生                          -------------------------\n");
	printf("--------------0,退出                              -------------------------\n");
	printf("---------------------------------------------------------------------------\n");
	printf("---------------------------------------------------------------------------\n");
	return _getch();
}


void edit_stud_menu(int id){
	Student *p = get_stud(id);
	if (p == NULL){
		printf("The student does not exist.\n");
		printf("Do you want to try a different ID? y/n\n");
		char temp=_getch();
		if (temp == 'y'){
			edit_stud_menu(input_id());
		}
	}
	else
	{
		
		while (1)
		{
			Student stud = *p;
			printf("---------------------------------------------------------------------------\n");
			printf("------------------------------学生信息-------------------------------------\n");
			printf("---------------------------姓名：%s----------------------------------------\n", stud.name);
			printf("---------------------------年龄：%d----------------------------------------\n", stud.age);
			printf("---------------------------性别：%s----------------------------------------\n", stud.gender);
			printf("---------------------------语文：%.2f----------------------------------------\n", stud.Chinese);
			printf("---------------------------数学：%.2f----------------------------------------\n", stud.Maths);
			printf("---------------------------英语：%.2f----------------------------------------\n", stud.English);
			printf("---------------------------总分：%.2f----------------------------------------\n", (stud.Chinese+stud.Maths+stud.English));
			printf("---------------------------------------------------------------------------\n");
			printf("-----------------1,编辑属性  2,删除资料  0,返回   -------------------------\n");
			printf("---------------------------------------------------------------------------\n");

			char option = _getch();
			switch (option)
			{
			case '1':
				edit_stud(&p);
				break;
			case '2':
				break;
			case '0':
				return;
			default:
				break;
			}
    
		}
	}
	
	
}

int input_id(){
	printf("Please input the ID you want to search:\n");
	fflush(stdin);
	int temp = -1;
	if (!scanf("%d", &temp)){
		printf("Please input digits only!\n");
		return input_id();
	}
	return temp;
}