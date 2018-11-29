#include "global.h"

//Imports from bianary file
void read_bfile(char *fname){
	FILE *fp;
	NODE p;
	fp = fopen(fname, "rb");
	if(fp==NULL){
		printf("Waiting list is empty\n");
		return;
	}
	printf("\nWAITING LIST\n");
	printf("Name\t\tDepartment\t\tDetails\n");
	printf("-------------------------------------------------------\n");
	while(fread(&p, sizeof(NODE), 1, fp)>0){
		printf("%s\t\t%d\t\t", p.name, p.department);
		switch(p.department){
			case 1:
				printf("Temperature: %f\n", p.details.fever);
				break;
			case 2:
				printf("Pain: %s\n", p.details.pain);
				break;
			case 3:
			case 4:
				printf("Days: %d\n", p.details.days);
				break;
		}
	}
	printf("-------------------------------------------------------\n");
	fclose(fp);
	return;
}

//Imports text file
void read_tfile(char *fname, int key){
	FILE *fp;
	char name[10], buffer[50];
	int i, size, department;
	union info details;
	fp = fopen(fname, "r");
	if(fp==NULL)
		return;
	fseek(fp, 26, SEEK_SET);
	while(fgets(buffer, 50, fp)!=NULL){
		for(i=0;buffer[i]!='\n';i++)
			buffer[i]=((buffer[i])^(key));
		sscanf(buffer, "%s\t%d", name, &department);
		switch(department){
			case 1:
				sscanf(buffer, "%s\t%d\t%f\n", name, &department, &details.fever);
				insert(name, department, details);
				break;
			case 2:
				sscanf(buffer, "%s\t%d\t%s\n", name, &department, details.pain);
				insert(name, department, details);
				break;
			case 3:
			case 4:
				sscanf(buffer, "%s\t%d\t%d\n", name, &department, &details.days);
				insert(name, department, details);
				break;
		}
	}
	fclose(fp);
	return;
}

//Saves list to text file
void write_tfile(char *fname, int key){
	FILE *fp;
	NODE *p;
	int i, j;
	char buffer[100];
	fp = fopen(fname, "w");
	fprintf(fp, "Name\t\tDepartment\t\tDetails\n");
	for(i=0;i<4;i++){
		p=wait_list[i].head;
		while(p!=NULL){
			switch(p->department){
			case 1:
				sprintf(buffer, "%s\t%d\t%f\n",p->name,p->department,p->details.fever);
				break;
			case 2:
				sprintf(buffer, "%s\t%d\t%s\n",p->name,p->department,p->details.pain);
				break;
			case 3:
			case 4:
				sprintf(buffer, "%s\t%d\t%d\n",p->name,p->department,p->details.days);
				break;
		}
		for(j=0;buffer[j]!='\n';j++)
			buffer[j]=((buffer[j])^(key));
			fprintf(fp, "%s", buffer);
			p=p->next;
		}
	}
	fclose(fp);
	return;
}


void *auto_save(void *arg){
	FILE *fp;
	NODE *p;
	int i;
	while(1){
		sleep(15);
		pthread_mutex_lock(&mutex);
		fp = fopen(arg, "wb");
		for(i=0;i<4;i++){
			p=wait_list[i].head;
			while(p!=NULL){
				fwrite(p, sizeof(NODE), 1, fp);
				p=p->next;
			}
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);
	}
}
