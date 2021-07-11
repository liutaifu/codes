#include <stdlib.h>
#include <stdio.h>



typedef struct single_list {
	struct single_list *next;
	int data;
} cycleList;

/*add node at tail*/
void  addNewNodeTail(cycleList *head,int item);
/*add node at head*/
void  addNewNodeHead(cycleList *head,int item);
/*delete node at head*/
void  deleteNodeHead(cycleList *head);
/*delete node at tail*/
void  deleteNodeTail(cycleList *head);
/*delete node by index*/
void  deleteNodeIndex(cycleList *head,cycleList *temp);
/*num of list*/
int numOfList(cycleList *head);
/*list is empty*/
int headIsEmpty(cycleList *head);
/*show list*/
void  showList(cycleList *head);
/*init list*/
cycleList *initList();

cycleList *initList()
{
	cycleList *head = (cycleList *)malloc(sizeof(cycleList));
	head->next = head;
	head->data = -1;
	return head;
}
void  addNewNodeTail(cycleList *head,int item)
{
	cycleList *temp = (cycleList *)malloc(sizeof(cycleList));
	cycleList *tempp = (cycleList *)malloc(sizeof(cycleList));

	tempp = head;
	while(head->next != tempp) {
		head = head->next;
	}
	temp->next = head->next;
	temp->data = item;
	head->next = temp;
}
void  addNewNodeHead(cycleList *head,int item)
{
	cycleList *temp = (cycleList *)malloc(sizeof(cycleList));
	temp->data = item;
	temp->next = head->next;
	head->next = temp;
}
void  deleteNodeHead(cycleList *head)
{
	cycleList *temp = (cycleList *)malloc(sizeof(cycleList));

	temp = head->next;

	if (head != head->next) {
		head->next = temp->next;
	}
}

void deleteNodeTail(cycleList *head)
{
	cycleList *temp = (cycleList *)malloc(sizeof(cycleList));
	cycleList *tempp = (cycleList *)malloc(sizeof(cycleList));

	temp = head;

	while(head != NULL) {
		if (head->next != temp) {
			tempp = head;
			head = head->next;
		} else {
			tempp->next = head->next;
			//head->next = NULL;
			break;
		}
	}
}

int numOfList(cycleList *head)
{
	int num = 0;
	cycleList *temp = (cycleList *)malloc(sizeof(cycleList));
	
	temp = head;

	while(head->next != temp) {
		num ++;
		head = head->next;
	}

	return num;
}

int headIsEmpty(cycleList *head)
{
	return (head->next != NULL) ? 0 : 1;
}
void deleteNodeIndex(cycleList *head, cycleList *temp) {
	cycleList *tt = (cycleList*)malloc(sizeof(cycleList));
	cycleList *tempp = (cycleList*)malloc(sizeof(cycleList));

	tt = head;
	tempp = head;
	printf("%3d %p %p ",tt->data,tt,temp);
	while(head->next != tt) {
		if (head->next != temp) {
		    tempp = head;
			head = head->next;
			printf("\n%3d %3d %p %p ",tempp->data,head->data,head,head->next);
		} else {
			if (tempp == head) {
				tempp->next = head->next->next;
			} else {
				tempp = tempp->next;
				head = head->next;
				tempp->next = head->next;
			}
			break;
		}
	}
}

cycleList *findNodeList(cycleList *head, int data)
{
	cycleList *temp = (cycleList*)malloc(sizeof(cycleList));
	cycleList *tempp = (cycleList*)malloc(sizeof(cycleList));
	
	temp = head;

	while(head->next != temp) {
	//while(head != NULL) {
		if (head->next->data == data) {
			tempp = head->next;
			break;
		} else {
			head = head->next;
		}
	}

	return tempp;
}

void  showList(cycleList *head)
{
	cycleList *temp = (cycleList*)malloc(sizeof(cycleList));
		
	temp = head;
	printf("list node \n");
	while(head->next != temp)
	{
//		printf(" %d %p\n",head->next->data,head->next);
		printf(" %d ",head->next->data);
		head = head->next;
	}
}

int main()
{
	int i = 0;
	cycleList *temp;
	temp = (cycleList *)malloc(sizeof(cycleList));

	cycleList *head = initList();
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

	printf("\n");

	temp = findNodeList(head,7);

	deleteNodeIndex(head, temp);
	printf("\nnum of list %d\n",numOfList(head));
	showList(head);

	return 0;
}
