#include <stdio.h>
#include <stdlib.h>
#include "../cyclelist.h"

extern cycleList *initList();
extern void  addNewNodeTail(cycleList *head,int item);
extern void  deleteNodeIndex(cycleList *head,cycleList *temp);


int main()
{
	int i = 0;
	int m = 0;
	int n = 0;
	cycleList *temp;
	temp = (cycleList *)malloc(sizeof(cycleList));

	cycleList *head = initList();


	scanf("%d",&m);
	scanf("%d",&n);

	printf("m:%d n:%d\n",m,n);

	for(i = 1; i <= m; i++) {
		addNewNodeTail(head, i);
	}
	showList(head);

	temp = head;
	i = 0;
	while(head != head->next) {
		if(head->next == temp) {
			head = head->next;
			continue;
		} else if(head->next->next == head) {
			break;
		} else {
			i ++;
			head = head->next;
		}
		if (i == n) {
			printf("delete i %d data %d\n",i,head->data);
			deleteNodeIndex(temp, head);
			i = 0;
		}
	}
	showList(temp);
	return 0;
}
