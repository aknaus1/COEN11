#include "global.h"

//Get department number from the user.
int get_department(){
	int department;
	while(1){
		scanf("%d", &department);
		if(IS_DEPT(department))
			break;
		else{
			printf("Sorry that is not a valid department.\n");
			printf("Please try again(1,2,3,4): ");
		}
	}
	return department;
}

//Check if a name is already in the list.
int check_duplicate (char name[]){
	int x, i;
	NODE *p;
	for(i=0;i<4;i++){
		p=wait_list[i].head;
		while(p!=NULL){
			x=strcmp(p->name, name);
			if(x==0){
				return 0;
			}
			p=p->next;
		}
	}
	return 1;
}

union info get_details(int department){
	union info details;
	switch(department){
		case 1:
			printf("What is your temperature?: ");
			scanf("%f", &details.fever);
			break;
		case 2:
			printf("Where is your pain?: ");
			scanf("%s", details.pain);
			break;
		case 3:
		case 4:
			printf("How many days have you felt sick?: ");
			scanf("%d", &details.days);
			break;
	}
	return details;
}

//Insert a name to the list.
void insert(char name[10], int department, union info details){
	NODE *p;
	p=(NODE *)malloc(sizeof(NODE));
	if(p==NULL){
		printf("System Error. Memory Full.");
		return;
	}
	strcpy(p->name, name);
	p->department=department;
		switch(department){
			case 1:
			p->details.fever=details.fever;
			break;
		case 2:
			strcpy(p->details.pain,details.pain);
			break;
		case 3:
		case 4:
			p->details.days=details.days;
			break;
	}
	if(wait_list[department-1].head==NULL){
		wait_list[department-1].head=p;
		wait_list[department-1].tail=p;
		p->next=NULL;
	}
	else{
		wait_list[department-1].tail->next=p;
		wait_list[department-1].tail=p;
		p->next=NULL;
	}
}

//Prints all the names in the list with the corresponding department and info
void list(){
	NODE *p;
	int i, x;
	x=1;
	printf("\nWAITING LIST\n");
	printf("Name\t\tDepartment\t\tDetails\n");
	printf("-------------------------------------------------------\n");
	for(i=0;i<4;i++){
		p=wait_list[i].head;
		while(p!=NULL){
			printf("%s\t\t%d\t\t", p->name, p->department);
			switch(p->department){
				case 1:
					printf("Temperature: %f\n", p->details.fever);
					break;
				case 2:
					printf("Pain: %s\n", p->details.pain);
					break;
				case 3:
				case 4:
					printf("Days: %d\n", p->details.days);
					break;
			}
			p=p->next;
			x++;
		}
	}
	printf("-------------------------------------------------------\n");
}

//Removes the oldest name from a given department
void rmv(){
	int department;
	printf("Which department is this for?: ");
	department=get_department();
	NODE *p;
	p=wait_list[department-1].head;
	if(p==NULL){
		printf("No one from that department is in the list.\n");
		return;
	}
	else{
		wait_list[department-1].head=p->next;
		free(p);
	}
}

//Shows the entries for a given department
void show_department(){
	NODE *p;
	int i, department, x;
	x=1;
	printf("Which department do you want to show?: ");
	department=get_department();
	printf("\nDEPARTMENT %d\n", department);
	printf("Name\t\tDetails");
	printf("\n---------------------------------------\n");
	p=wait_list[department-1].head;
	while(p!=NULL){
		printf("%s\t\t", p->name);
		switch(department){
			case 1:
				printf("Temperature: %f\n", p->details.fever);
				break;
			case 2:
				printf("Pain: %s\n", p->details.pain);
				break;
			case 3:
			case 4:
				printf("Days: %d\n", p->details.days);
				break;
		}
		x++;
		p=p->next;
	}
	printf("---------------------------------------\n");
}

//Shows the corresponding info for a given person
void show_info(){
	int x, i;
	char name[10];
	NODE *p;
	printf("Who is this for?: ");
	scanf("%s", name);
	for(i=0; i<4; i++){
		p=wait_list[i].head;
		while(p!=NULL){
			x=strcmp(p->name, name);
			if(x==0){
				printf("INFO\n");
				printf("--------------\n");
				printf("NAME: %s\nDEPARTMENT: %d\n", p->name, p->department);
				switch(p->department){
					case 1:
						printf("TEMPERATURE: %f\n", p->details.fever);
						break;
					case 2:
						printf("PAIN: %s\n", p->details.pain);
						break;
					case 3:
					case 4:
						printf("DAYS: %d\n", p->details.days);
						break;
				}
				printf("--------------\n");
				return;
			}
			p=p->next;
		}
	}
	printf("Sorry that name is not in the list.\n");
}

//Moves a name from one department to another
void change_department(){
	int department, i, q;
	q=0;
	char name[10];
	union info details;
	NODE *p, *temp;
	printf("Who is this for?: ");
	scanf("%s", name);
	for(i=0; i<4; i++){
		p=temp=wait_list[i].head;
		if(p!=NULL){
			if(strcmp(p->name,name)==0){
				q=1;
				break;
			}
			p=p->next;
			while(p!=NULL){
				if(strcmp(p->name,name)==0){
					q=1;
					break;
				}
				p=p->next;
				temp=temp->next;
			}
			if(q==1)
				break;
		}
		if(i+1==4){
			printf("Sorry that name is not in the list.\n");
			return;
		}
	}
	if(p==wait_list[i].head){
		wait_list[i].head=p->next;
		free(p);
	}
	else if(p==wait_list[i].tail){
		wait_list[i].tail=temp;
		wait_list[i].tail->next=NULL;
		free(p);
	}
	else{
		temp->next=p->next;
        	free(p);
	}
	printf("What department do you want to move into?: ");
	department = get_department();
	details=get_details(department);
	insert(name, department, details);
}
