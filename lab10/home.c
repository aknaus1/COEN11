#include "global.h"
struct head_tail wait_list[4];
pthread_mutex_t mutex;

int main(int arg, char *argu[]){
	int i, x, department, key;
	char name[10];
	union info details;
	for(i=0;i<4;i++){
		wait_list[i].head=NULL;
		wait_list[i].tail=NULL;
	}
	if(arg!=4){
		printf("ERROR: NOT ENEOUGH ARGUMENTS");
		return 0;
	}
	key=atoi(argu[3]);
	read_tfile(argu[1],key);
	printf("END\n");
	pthread_t thr;
	pthread_mutex_init (&mutex, NULL);
	pthread_create (&thr, NULL, auto_save, (void *)argu[2]);
	while(1){
		printf("\t\t\tOptions\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("1:Add Name\t\t2:View List\t\t3:Remove Name from Department\n");
		printf("4:Show Department\t5:Person Info\t\t");
		printf("6:Change Persons Department\n7:Read Bianary File\t\t0:Save and Quit\n");
		printf("Entry: ");
		scanf("%d", &x);
		if(x==0)
			break;
		switch(x){
			case 1:
				pthread_mutex_lock(&mutex);
				printf ("What is your name?: ");
				scanf ("%s", name);
				if(check_duplicate(name)==0){
					printf("Sorry that name is already in the list.\n");
					pthread_mutex_unlock(&mutex);
					break;
				}
				printf("What department is this for?: ");
				department=get_department();
				details=get_details(department);
				insert(name, department, details);
				pthread_mutex_unlock(&mutex);
				break;
			case 2:
				list();
				break;
			case 3:
				pthread_mutex_lock(&mutex);
				rmv();
				pthread_mutex_unlock(&mutex);
				break;
			case 4:
				show_department();
				break;
			case 5:
				show_info();
				break;
			case 6:
				pthread_mutex_lock(&mutex);
				change_department();
				pthread_mutex_unlock(&mutex);
				break;
			case 7:
				pthread_mutex_lock(&mutex);
				read_bfile(argu[2]);
				pthread_mutex_unlock(&mutex);
				break;
		}
	}
	pthread_mutex_lock(&mutex);
	pthread_cancel(thr);
	write_tfile(argu[1],key);
}
