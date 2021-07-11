#include <stdlib.h>
#include <stdio.h>



typedef struct list {
	struct list *next;
	struct list *prior;
	int data;
} dualList;


/*add node at tail*/
void  addNewNodeTail(dualList *head,int item);
/*add node at head*/
void  addNewNodeHead(dualList *head,int item);
/*delete node at head*/
void  deleteNodeHead(dualList *head);
/*delete node at tail*/
void  deleteNodeTail(dualList *head);
/*delete node by index*/
void  deleteNodeIndex(dualList *head,dualList *temp);
/*num of list*/
int numOfList(dualList *head);
/*list is empty*/
int headIsEmpty(dualList *head);
/*show list*/
void  showList(dualList *head);
/*init list*/
dualList *initList();

dualList *initList()
{
	dualList *head = (dualList *)malloc(sizeof(dualList));
	head->next = NULL;
	head->prior = NULL;
	head->data = -1;
	return head;
}
void  addNewNodeTail(dualList *head,int item)
{
	dualList *temp = (dualList *)malloc(sizeof(dualList));
#if 0
	dualList *temph = (dualList *)malloc(sizeof(dualList));
	while(head)
	{
		temph = head;
		head = head->next;
	}
	temp->next = NULL;
	temp->data = item;
	temp->prior = temph;
	temph->next = temp;
#else
	while(head->next != NULL) {
		head = head->next;
	}
	temp->next = NULL;
	temp->data = item;
	temp->prior = head;
	head->next = temp;
#endif
	printf("list add  %d\n",item);
}
void  addNewNodeHead(dualList *head,int item)
{
	dualList *temp = (dualList *)malloc(sizeof(dualList));
	temp->data = item;
	temp->next = head->next;
	temp->prior = head;
	head->next->prior = temp;
	head->next = temp;
	printf("list add  %d\n",item);
}
void  deleteNodeHead(dualList *head)
{
	dualList *temp = (dualList *)malloc(sizeof(dualList));

#if 0
	temp = head->next;
		
	while(temp != NULL) {
		if (temp != NULL) {
			temp = temp->next;
			head->next = temp;
			temp->prior = head;
		}
	}
#else
	temp = head->next;
	if (temp != NULL) {
		temp = temp->next;
		head->next = temp;
		temp->prior = head;
	}
#endif
}
void deleteNodeTail(dualList *head)
{
	while(head != NULL) {
		if (head->next != NULL && head->next->next != NULL) {
			head = head->next;
		} else {
			head->next = NULL;
			break;
		}
	}
}
void deleteNodeIndex(dualList *head, dualList *temp) {
	dualList *tempp = (dualList*)malloc(sizeof(dualList));

#if 0
	/*
	   如果需要删除的点在尾部，删除失败
	 */
	while(head->next != NULL) {
		if (head != temp) {
		    tempp = head;
			head = head->next;
		} else {
			tempp->next = head->next;
			head->next->prior = tempp;
			break;
		}
	}
#else
	while(head != NULL) {
		if (head->next != temp) {
		    tempp = head;
			head = head->next;
		} else {
			if (head->next->next != NULL) {
				tempp = tempp->next;
				head = head->next;
				tempp->next = head->next;
				head->next->prior = tempp;
			} else {
				head->next = NULL;
			}
			break;
		}
	}
#endif
}

int numOfList(dualList *head)
{
	int num = 0;
	while(head->next != NULL) {
		num ++;
		head = head->next;
	}

	return num;
}

int headIsEmpty(dualList *head)
{
	return (head->next != NULL) ? 0 : 1;
}

dualList *findNodeList(dualList *head, int data)
{
	dualList *tempp = (dualList*)malloc(sizeof(dualList));
	
	while(head != NULL) {
		if (head->data == data) {
			tempp = head;
			break;
		} else {
			head = head->next;
		}
	}

	return tempp;
}

void  showList(dualList *head)
{
#if 0
	dualList *temp = (dualList *)malloc(sizeof(dualList));
	dualList *tempp = (dualList *)malloc(sizeof(dualList));

	temp = head->next;
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
#else 
	printf("clockwise list node \n");
	while(head->next != NULL) {
		printf(" %d ",head->next->data);
		head = head->next;
	}

	printf("\n counterclockwise list node \n");
	while(head->prior != NULL) {
		printf(" %d ",head->data);
		head = head->prior;
	}
	printf("\n");
#endif
}

int main()
{
	int i = 0;
	dualList *temp = (dualList *)malloc(sizeof(dualList));

	dualList *head = initList();
	printf("list nodea \n");
	for (i = 0 ; i < 5 ; i ++)
		addNewNodeTail(head,i);
				
	printf("list nodeb \n");
	for (i = 10 ; i > 5 ; i --)
		addNewNodeHead(head,i);
	printf("list nodec \n");

	showList(head);

	printf("\nnum of list %d\n",numOfList(head));
	printf("\nhead is empty %d\n",headIsEmpty(head));
	deleteNodeHead(head);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);
	deleteNodeTail(head);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);

	temp = findNodeList(head,3);

	deleteNodeIndex(head, temp);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);

	return 0;
}
