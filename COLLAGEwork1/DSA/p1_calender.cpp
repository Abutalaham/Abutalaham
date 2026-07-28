#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct element{
	char *day;
	int date;
	char *activity;
};
struct element * create(){
	struct element *calender;
	calender = (struct element*)malloc(7 * sizeof(struct element));
	return calender;
}
void read(struct element *calender){
	int date;
	char day[15];
	char activity[15];
	int i;
	for (i=0;i<7;i++){
		printf("\nday:");
		scanf("%s",day);
		calender[i].day=(char*)malloc(strlen(day)+1);
		strcpy(calender[i].day,day);
		printf("\ndate:");
		scanf("%d",&calender[i].date);
		printf("\nactivity:");
		scanf("%s",activity);
		calender[i].activity=(char*)malloc(strlen(activity)+1);
		strcpy(calender[i].activity,activity);	
	}
}
void display(struct element *calender){
	int i;
	printf("\nDAY\tDATE\tACTIVITY\n");
	for (i=0;i<7;i++){
		printf("%s\t%d\t%s\n",
               calender[i].day,
               calender[i].date,
               calender[i].activity);
	}
}
int main(){
	struct element *calender;
	calender=create();
	read(calender);
	display(calender);
	free(calender);
	return 0;
}











