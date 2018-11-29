#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a=0;
struct list{
	int dpt;
	char name[10];
};

struct list wl[10];



//Adds a name to the waitlist
void insert(){
	if(a<10){
		int x=0;
		int i;
		char user[10];
		while(x==0){
        		printf("Whats your name?: ");
			scanf("%s", user);
			x=check_duplicate(user);
			if(x==0)
				printf("Sorry that name is already in the list.\n");
		}
		wl[a].dpt=get_dept();
		strcpy(wl[a].name,user);
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
		printf("%d: %s", z, p->name);
		if(p->dpt!='\0')
			printf("					Dept# %d", p->dpt);
		printf("\n");
		z++, p++;
	}
	printf("\n");
}


//Checks if the name is already in the list
int check_duplicate(char array[]){
	int i;
	struct list *p=wl;
	for(i=0; i<10; i++){
		if(strcmp(p->name, array)==0)
			return 0;
		if(i+1==10)
			return 1;
		p++;
	}
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
			printf("%d: %s \n", z, p->name);
			z++;
		}
		p++;
	}
	for(i=z; i<11; i++){
		printf("%d: \n", z);
		z++;
	}
}


//Main Function
int main (void){
	while(1){
		int r;
		printf("Enter 1 to add a name, 2 to view list, 3 to remove the oldest name from a department, ");
		printf("4 to show entries for a department, and 0 to Quit: ");
		scanf("%d", &r);
		if(r==1)
			insert();
		else if(r==2)
			list();
		else if(r==3)
			rmv();
		else if(r==4)
			show_dept();
		else
			break;
	}
}
