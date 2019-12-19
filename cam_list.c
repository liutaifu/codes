#include <stdlib.h>
#include <stdio.h>



typedef struct single_list {
		struct single_list *next;
		int data;
} sin_list;


void  addNewNodeTail(sin_list *head,int item);
void  addNewNodeHead(sin_list *head,int item);
void  deleteNewNodeHead(sin_list *head,int item);
void  showList(sin_list *head);
sin_list *initList();

sin_list *initList()
{
		sin_list *head = (sin_list *)malloc(sizeof(sin_list));
		head->next = NULL;
		head->data = NULL;
		return head;
}
void  addNewNodeTail(sin_list *head,int item)
{
		sin_list *temp = (sin_list *)malloc(sizeof(sin_list));
		sin_list *temph = (sin_list *)malloc(sizeof(sin_list));
		//temp = head;
		while(head)
		{
				temph = head;
				head = head->next;
		}
		temp->next = NULL;
		temp->data = item;
		temph->next = temp;
		printf("list node0 \n");
}
void  addNewNodeHead(sin_list *head,int item)
{
		sin_list *temp = (sin_list *)malloc(sizeof(sin_list));
		temp->data = item;
		temp->next = head->next;
		head->next = temp;
}
void  deleteNewNodeHead(sin_list *head,int item)
{
}
void  showList(sin_list *head)
{
		sin_list *temp = head->next;
		printf("list node \n");
		while(temp)
		{
				printf(" %d ",temp->data);
				temp = temp->next;
		}
}

int main()
{
		int i = 0;
		sin_list *temp;

		sin_list *head = initList();
		printf("list nodea \n");
		for (i = 0 ; i < 5 ; i ++)
				addNewNodeTail(head,i);
				
		printf("list nodeb \n");
		for (i = 10 ; i > 5 ; i --)
				addNewNodeHead(head,i);
		printf("list nodec \n");

		showList(head);
		return 0;
}
