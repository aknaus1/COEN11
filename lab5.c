#include <stdio.h>
#include <string.h>
#include <stdlib.h>

union extra{
	float fever;
	char pain[10];
	int days;
};

#define NODE struct node
struct node{
	int department;
	char name[10];
	union extra details;
	NODE *next;
};
NODE *head = NULL;
NODE *tail = NULL;

//Check if a name is already in the list.
int check_duplicate (char name[]){
	int x;
	NODE *p;
	p=head;
	while(p!=NULL){
		x=strcmp(p->name, name);
		if(x==0){
		return 0;
		}
		p=p->next;
	}
	return 1;
}

//Get department number from the user.
int get_department(){
	int department;
	while(1){
		printf("What department is this for?(1,2,3,4): ");
		scanf("%d", &department);
		if(department==1||department==2||department==3||department==4)
			break;
		else
			printf("Sorry that is not a valid department.\n");
	}
	return department;
}

//Insert a name to the list.
void insert (){
	int i;
	NODE *p, *temp;
	char name[10];
	printf ("What is your name?: ");
	scanf ("%s", name);
	if(check_duplicate(name)==0){
		printf("Sorry that name is already in the list.\n");
		return;
	}
	p=(NODE *)malloc(sizeof(NODE));
	if(p==NULL){
		printf("System Error. Memory Full.");
		return;
	}
	strcpy(p->name, name);
	p->department=get_department();
	switch(p->department){
		case 1:
			printf("What is your temperature?: ");
			scanf("%f", &p->details.fever);
			break;
		case 2:
			printf("Where is your pain?: ");
			scanf("%s", p->details.pain);
			break;
		case 3:
		case 4:
			printf("How many days have you felt sick?: ");
			scanf("%d", &p->details.days);
			break;
	}
	if(head==NULL){
                p->next=NULL;
		head=p;
		tail=p;
        }
        else{
                tail->next=p;
                tail=p;
		p->next=NULL;
        }
}

//Prints all the names in the list with the corresponding department and info
void list(){
	NODE *p;
	if(head==NULL){
		printf("The list is empty.\n");
		return;
	}
	printf("WAITING LIST\n");
	p=head;
	int x=1;
	while(p!=NULL){
		printf("%d. Name: %s\t\tDepartment: %d\t\t", x, p->name, p->department);
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

//Removes the oldest name from a given department
void rmv(){
	int department;
	department=get_department();
	NODE *p, *q;
	p=q=head;
	while(p!=NULL){
		if(p->department==department)
			break;
		q=p;
		p=p->next;
	}
	if(p==NULL){
		printf("No one from that department is in the list.\n");
		return;
	}
	if(p==head){
		head=p->next;
		free(p);
	}
	else if(p==tail){
		tail=q;
		q->next=NULL;
		free(p);
	}	
	else{
		q->next=p->next;
		free(p);
		
	}
}

//Shows the entries for a given department
void show_department(){
	int d;
	d=get_department();
	NODE *p;
	while(p!=NULL){
		if(p->department==d)
			break;
		if(p->next==NULL){
			printf("There are no entries for this department.\n");
			return;
		}
		p=p->next;
	}
	printf("Department %d\n", d);
	p=head;
	int x=1;
	while(p!=NULL){
		if(p->department==d){
			printf("%d.Name: %s\t\t", x, p->name);
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
			x++;
		}
		p=p->next;
	}
}

//Shows the corresponding info for a given person.
void show_info(){
	int x;
	char name[10];
	NODE *p;
	p=head;
	printf("Who is this for?: ");
	scanf("%s", name);
	while(p!=NULL){
		x=strcmp(p->name, name);
		if(x==0){
			printf("Name: %s\t\tDepartment: %d\t\t", p->name, p->department);
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
			return;
		}
		p=p->next;
	}
	printf("Sorry that name is not in the list.\n");
}

int main (){
	while(1){
		int x;
		printf("Enter 1 to add a name, 2 to view list, ");
		printf("3 to remove the oldest name from a department, ");
		printf("4 to show entries for a department, ");
		printf("5 to show corresponding info for a person, and 0 to Quit: ");
		scanf("%d", &x);
		if(x==0)
			break;
		switch(x){
			case 1:
				insert();
				break;
			case 2:
				list();
				break;
			case 3:
				rmv();
				break;
			case 4:
				show_department();
				break;
			case 5:
				show_info();
				break;
		}
	}
	printf("Thank you for coming!\n");
}

