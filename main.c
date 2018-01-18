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
	printf("-------------------------ѧ����Ϣ����ϵͳ----------------------------------\n");
	printf("---------------------------------------------------------------------------\n");
	printf("--------------1,����ѧ��                          -------------------------\n");
	printf("--------------2,�������ݿ�                        -------------------------\n");
	printf("--------------3,�༭ѧ��                          -------------------------\n");
	printf("--------------0,�˳�                              -------------------------\n");
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
			printf("------------------------------ѧ����Ϣ-------------------------------------\n");
			printf("---------------------------������%s----------------------------------------\n", stud.name);
			printf("---------------------------���䣺%d----------------------------------------\n", stud.age);
			printf("---------------------------�Ա�%s----------------------------------------\n", stud.gender);
			printf("---------------------------���ģ�%.2f----------------------------------------\n", stud.Chinese);
			printf("---------------------------��ѧ��%.2f----------------------------------------\n", stud.Maths);
			printf("---------------------------Ӣ�%.2f----------------------------------------\n", stud.English);
			printf("---------------------------�ܷ֣�%.2f----------------------------------------\n", (stud.Chinese+stud.Maths+stud.English));
			printf("---------------------------------------------------------------------------\n");
			printf("-----------------1,�༭����  2,ɾ������  0,����   -------------------------\n");
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