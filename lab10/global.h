#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define IS_DEPT(x) ((x)>=1 && (x)<=4)
#define NODE struct node

union info{
	float fever;
	char pain[10];
	int days;
};

struct node{
	int department;
	char name[10];
	union info details;
	NODE *next;
};

struct head_tail{
	NODE *head;
	NODE *tail;
};

extern pthread_mutex_t mutex;
extern struct head_tail wait_list[4];

extern void *auto_save(void *arg);
extern union info get_details(int department);
extern int get_department();
extern int check_duplicate (char name[]);
extern void insert(char name[10], int department, union info details);
extern void list();
extern void rmv();
extern void show_department();
extern void show_info();
extern void change_department();
extern void read_bfile(char *fname);
extern void read_tfile(char *fname, int key);
extern void write_tfile(char *fname, int key);



