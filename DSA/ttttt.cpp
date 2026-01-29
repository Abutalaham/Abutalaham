#include<stdio.h>
#include<stdlib.h>
struct student{
	char ssn[20],name[20],prog[20],phno[15];
	int date;
	struct student *next;
};
struct student *head = NULL;
struct student * create(){
	struct student *newnode;
	newnode = (struct student*)malloc(sizeof(struct student));
	printf("\nENTER SSN:");
	scanf("%s",newnode->ssn);
	printf("\nENTER NAME:");
	scanf("%[^\n]",newnode->name);
	printf("\nENTER date:");
	scanf("%d",&newnode->date);
	printf("\nENTER prog:");
	scanf("%[^\n]",newnode->prog);
	printf("\nENTER phno:");
	scanf("%s",newnode->phno);
	newnode->next  = NULL;
	return newnode;
}
void insertfront(){
	struct student *newnode;
	newnode = create();
	if(head == NULL){
		head = newnode;
		return;
	}
	newnode->next = head;
	head = newnode;
	return;
}
void insertend(){
	struct student *newnode;
	newnode = create();
	struct student *temp;
	temp = head;
	if(head == NULL){
		head = newnode;
		return;
	}
	if(head->next == NULL){
		head->next = newnode;
		return;
	}
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newnode;
	return;
}
void deletefront(){
	if(head == NULL){
		printf("list is empty");
		return;
	}
	if(head->next == NULL){
		free(head);
		head = NULL;
		return;
	}
	struct student *temp;
	temp = head;
	head = head->next;
	free(temp);
	return;
}
void deleteend(){
	struct student *temp,*prev;
	temp = head;
	if(head == NULL){
		printf("list is empty");
		return;
	}
	if(head->next == NULL){
		free(head);
		head = NULL;
		return;
	}
	while(temp->next != NULL){
		prev = temp;
		temp = temp->next;
	}
	prev->next = NULL;
	free(temp);
	
}
void display(){
	if(head == NULL){
		printf("list is empty");
		return;
	}
	struct student *temp;
	temp = head;
	printf("student list:\n");
	while (temp != NULL)
    {
        printf("\nUSN: %s", temp->ssn);
        printf("\nName: %s", temp->name);
        printf("\nProgramme: %s", temp->prog);
        printf("\nSemester: %d", temp->date);
        printf("\nPhone: %s\n", temp->phno);

        temp = temp->next;
    }
    return;
}
int main()
{
    int choice;

    while (1)
    {
        printf("\n1.Insert Front");
        printf("\n2.Insert End");
        printf("\n3.Delete Front");
        printf("\n4.Delete End");
        printf("\n5.Display");
        printf("\n6.Exit");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: insertfront(); break;
            case 2: insertend(); break;
            case 3: deletefront(); break;
            case 4: deleteend(); break;
            case 5: display(); break;
            case 6: return 0;
            default: printf("Invalid Choice\n");
        }
    }
}










