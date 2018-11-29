#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char wl [10][20];
int dpt[10];
int a=0;


//Adds a name to the waitlist
void insert(){
	if(a<10){
		int x=0;
		int i;
		char name[20];
		int dept;
		while(x==0){
        		printf("Whats your name?: ");
       			scanf("%s", name);
			int j;
//Checks if name is already on list
			for(i=0; i<10; i++){	
				if(strcmp(wl[i],name)==0){
					printf("Sorry that name is already in the list. :( \n");
					break;
				}
				if(i+1==10)
					x=1;
			}
		}
		x=0;
		while(x==0){
		printf("What department are you?:(1,2,3,4): ");
		scanf("%d", &dept);
			if(dept==1||dept==2||dept==3||dept==4)
				break;
			printf("Sorry thats not a department. \n");
		}
		dpt[a]=dept;
//Adds name to list
		for(i=0; name[i]!='\0'; i++){
			wl[a][i] = name[i];
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
	for(i=0; i<10; i++){
		printf("%d: ", z);
		for(j=0; wl[i][j]!='\0'; j++){
			printf("%c", wl[i][j]);
		}
		if(dpt[i]!='\0')
			printf("		Dept# %d", dpt[i]);
		printf("\n");
		z++;
	}
	printf("\n");
}

int main (void){
	while(1){
		int r;
		printf("Enter 1 to add a name, enter 2 to view list or enter 0 to quit: ");
		scanf("%d", &r);
		if(r==1){
			insert();
		}
		else if(r==2){
			list();
		}
		else
			break;
	}
}
