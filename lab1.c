#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {        
	int a, b, c, user;
	int y=0;
	srand((int) time(NULL));
	int x;
	for(x=0; x<10; x++){
        	b = rand()%12 + 1;
        	c = rand()%13;
        	a = b * c;
        	printf("%d/%d=?\n",a ,b);
		scanf("%d", &user);
        	if (user==c){	
            		printf("Correct!\n");
			y++;
        	}
		else if(user!=c){
        		printf("Incorrect.\n");
		}
	}
	printf("You got %d correct!", y);
}
