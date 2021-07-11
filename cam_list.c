#include <stdlib.h>
#include <stdio.h>



typedef struct single_list {
		struct single_list *next;
		int data;
} sinList;

/*add node at tail*/
void  addNewNodeTail(sinList *head,int item);
/*add node at head*/
void  addNewNodeHead(sinList *head,int item);
/*delete node at head*/
void  deleteNodeHead(sinList *head);
/*delete node at tail*/
void  deleteNodeTail(sinList *head);
/*delete node by index*/
void  deleteNodeIndex(sinList *head,sinList *temp);
/*num of list*/
int numOfList(sinList *head);
/*list is empty*/
int headIsEmpty(sinList *head);
/*show list*/
void  showList(sinList *head);
/*init list*/
sinList *initList();

sinList *findNodeList(sinList *head, int data);

sinList *initList()
{
	sinList *head = (sinList *)malloc(sizeof(sinList));
	head->next = NULL;
	head->data = -1;
	return head;
}
void  addNewNodeTail(sinList *head,int item)
{
	sinList *temp = (sinList *)malloc(sizeof(sinList));
#if 0
	sinList *temph = (sinList *)malloc(sizeof(sinList));
	while(head)
	{
			temph = head;
			head = head->next;
	}
	temp->next = NULL;
	temp->data = item;
	temph->next = temp;
#else
	while(head->next != NULL) {
		head = head->next;
	}
	temp->next = NULL;
	temp->data = item;
	head->next = temp;
#endif
}
void  addNewNodeHead(sinList *head,int item)
{
	sinList *temp = (sinList *)malloc(sizeof(sinList));
	temp->data = item;
	temp->next = head->next;
	head->next = temp;
}
void  deleteNodeHead(sinList *head)
{
	sinList *temp = (sinList *)malloc(sizeof(sinList));

	temp = head->next;
	if (temp != NULL) {
		temp = temp->next;
		head->next = temp;
	}
}

void deleteNodeTail(sinList *head)
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

int numOfList(sinList *head)
{
	int num = 0;
	while(head->next != NULL) {
		num ++;
		head = head->next;
	}

	return num;
}

int headIsEmpty(sinList *head)
{
	return (head->next != NULL) ? 0 : 1;
}
void deleteNodeIndex(sinList *head, sinList *temp) {
	sinList *tempp = (sinList*)malloc(sizeof(sinList));

	while(head != NULL) {
		if (head->next != temp) {
		    tempp = head;
			head = head->next;
		} else {
			if (head->next->next != NULL) {
				tempp = tempp->next;
				head = head->next;

				tempp->next = head->next;
			}
			else {
				head->next = NULL;
			}
			break;
		}
	}
}

sinList *findNodeList(sinList *head, int data)
{
	sinList *tempp = (sinList*)malloc(sizeof(sinList));
	
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

void  showList(sinList *head)
{
	sinList *temp = head->next;
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
	sinList *temp;
	temp = (sinList *)malloc(sizeof(sinList));

	sinList *head = initList();
	for (i = 0 ; i <= 5 ; i ++)
		addNewNodeTail(head,i);
			
	for (i = 10 ; i > 5 ; i --)
		addNewNodeHead(head,i);

	showList(head);

	printf("\nnum of list %d\n",numOfList(head));
	printf("\nhead is empty %d\n",headIsEmpty(head));
	deleteNodeHead(head);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);
	deleteNodeTail(head);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);


	temp = findNodeList(head,4);

	deleteNodeIndex(head, temp);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);

	return 0;
}
