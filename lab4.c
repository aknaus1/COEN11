#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int get_dept();
int check_duplicate(char array[]);
int a=0;
union Patient{
	float fever;
	char pain[30];
	int day;
};


struct list{
	int dpt;
	char name[10];
	union Patient details;
};

struct list wl[10];


//Adds a name to the waitlist
void insert(){
	if(a<10){
		int x=0;
		int i, dept, num, days;
		char user[10];
		float temp;
		char pain[30];
		while(x==0){
        		printf("Whats your name?: ");
			scanf("%s", user);
			x=check_duplicate(user);
			if(x==0)
				printf("Sorry that name is already in the list.\n");
		}
		dept=get_dept();
		wl[a].dpt=dept;
		strcpy(wl[a].name,user);
		switch(dept){
			case 1:
				printf("What is your temperature?: ");
				scanf("%f", &wl[a].details.fever);
				//wl[a].details.fever=temp;
				break;
			case 2:
				printf("Where is your pain?: ");
				scanf("%s", wl[a].details.pain);
				//strcpy(wl[a].details.pain, pain);
				break;
			case 3:
			case 4:
				printf("How many days have you felt sick?: ");
				scanf("%d", &wl[a].details.day);
				//wl[a].details.day=days;
				break;
		}
		a++;
	}
	else
		printf("Sorry waiting list is full. :( \n");
}


//List the names on the waitlist
void list(){
	int i, j;
	int z=1;
	struct list *p = wl;
	printf("WAITING LIST: \n");
	for(i=0; i<10; i++){
		printf("%d: ", z);
		printf("%s	", p->name);
		if(p->dpt!='\0'){
			printf("		Dept#: %d	", p->dpt);
			switch(p->dpt){
				case 1:
					printf("		Temperature: %f", p->details.fever);
					break;
				case 2:
					printf("		Pain: %s", p->details.pain);
					break;
				case 3:
				case 4:
					printf("		Days: %d", p->details.day);
					break;
			}
		}
		printf("\n");
		z++, p++;
	}
	printf("\n");
}


//Checks if the name is already in the list
int check_duplicate(char array[]){
	int i, x=1;
	struct list *p=wl;
	for(i=0; i<10; i++){
		if(strcmp(p->name, array)==0)
			x= 0;
		p++;
	}
	return x;
}


//Gets department number from the user
int get_dept(){
	int dept;
	while(1){
		printf("What department is this for?(1,2,3,4): ");
		scanf("%d", &dept);
		if(dept==1||dept==2||dept==3||dept==4){
			return dept;
			break;
		}
		printf("Sorry thats not a department. \n");
	}
}


//Remove the oldest item with the dept given
void rmv(){
	int i,x;
	int dept=get_dept();
	struct list *p=wl;
	for(i=0; i<10; i++){
		if (p->dpt == dept){
			x=i;
			break;
		}
		if(i+1==10)
			x=10;
		p++;
	}
	if(x!=10){
		for(i=x; i<10; i++){
			p->dpt=wl[i+1].dpt;
			strcpy(p->name,wl[i+1].name);
			switch(wl[i+1].dpt){
				case 1:
					p->details.fever=wl[i+1].details.fever;
					break;
				case 2:
					strcpy(p->details.pain,wl[i+1].details.pain);
					break;
				case 3:
				case 4:
					p->details.day=wl[i+1].details.day;
			}
			p++;
		}
		a--;
	}
}


//Show the entries in the list that matches the dept
void show_dept(){
	int i, j;
	int z=1;
	int dept=get_dept();
	struct list *p=wl;
	printf("Department %d: \n", dept);
	for(i=0; i<10; i++){
		if(p->dpt==dept){
			printf("%d: %s	", z, p->name);
			switch(p->dpt){
				case 1:
					printf("		Temperature: %f\n", p->details.fever);
					break;
				case 2:
					printf("		Pain Area: %s\n", p->details.pain);
					break;
				case 3:
				case 4:
					printf("		Day(s): %d\n", p->details.day);
					break;
			}
			z++;
		}
		p++;
	}
	for(i=z; i<11; i++){
		printf("%d: \n", z);
		z++;
	}
}


//Shows info about a specific person
void showinfo(){
	char person[10];
	struct list *p=wl;
	int i;
	printf("Who is this for?: ");
	scanf("%s", person);
	if(check_duplicate(person)==0){
		for(i=0; i<10; i++){
			if(strcmp(p->name, person)==0){
				printf("Name: %s\n", p->name);
				printf("Department: %d\n", p->dpt);
				switch(p->dpt){
					case 1:
						printf("Fever: %f\n", p->details.fever);
						break;
					case 2:
						printf("Kind of Pain: %s\n", p->details.pain);
						break;
					case 3:
					case 4:
						printf("Has been sick for %d days.\n", p->details.day);
						break;
				}
			}
			p++;
		}
	}
	else
		printf("Sorry that name is not in the list.\n");
}


//Main Function
int main (void){
	while(1){
		int r;
		printf("Enter 1 to add a name, 2 to view list, 3 to remove the oldest name from a department, ");
		printf("4 to show entries for a department, 5 to show corresponding info for a person, and 0 to Quit: ");
		scanf("%d", &r);
		if(r==1)
			insert();
		else if(r==2)
			list();
		else if(r==3)
			rmv();
		else if(r==4)
			show_dept();
		else if(r==5)
			showinfo();
		else
			break;
	}
}
