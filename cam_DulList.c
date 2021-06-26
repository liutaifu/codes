#include <stdlib.h>
#include <stdio.h>



typedef struct list {
		struct list *next;
		struct list *prior;
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
		head->prior = NULL;
		head->data = NULL;
		return head;
}
void  addNewNodeTail(sin_list *head,int item)
{
		sin_list *temp = (sin_list *)malloc(sizeof(sin_list));
		sin_list *temph = (sin_list *)malloc(sizeof(sin_list));
		while(head)
		{
	
				temph = head;
				head = head->next;
		}
		temp->next = NULL;
		temp->data = item;
		temp->prior = temph;
		temph->next = temp;
		printf("list add  %d\n",item);
}
void  addNewNodeHead(sin_list *head,int item)
{
		sin_list *temp = (sin_list *)malloc(sizeof(sin_list));
		temp->data = item;
		temp->next = head->next;
		head->next->prior = temp;
		head->next = temp;
		printf("list add  %d\n",item);
}
void  deleteNewNodeHead(sin_list *head,int item)
{
}
void  showList(sin_list *head)
{
		sin_list *temp = head->next;
		sin_list *tempp;
		printf("clockwise list node \n");
		while(temp)
		{
				tempp = temp;
				printf(" %d ",temp->data);
				temp = temp->next;
		}
		printf("\n counterclockwise list node \n");
		while(tempp)
		{
				printf(" %d ",tempp->data);
				tempp = tempp->prior;
		}
		printf("\n");
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

		temp = head;
		showList(temp);
		return 0;
}
