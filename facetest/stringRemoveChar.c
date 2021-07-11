#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *first = NULL;
	char *sec = NULL;
	char *temp = NULL;
	int i = 0;
	int j = 0;
	int k = 0;

	first = (char*)malloc(sizeof(char) * 1024);
	sec = (char*)malloc(sizeof(char) * 1024);
	temp = (char*)malloc(sizeof(char) * 1024);
	
	printf("please do not input more than 1024\n");
	scanf("%[^\n]",first);
	scanf("%s",sec);


	printf("first %s\n",first);
	printf("sec %s\n",sec);


	while(sec[i] != '\0') {
		while(first[j] != '\0') {
			if (first[j] != sec[i]) {
				temp[k++] = first[j];
			}
			j++;
		}
		for(j = 0; j < k; j ++) {
			first[j] = temp[j];
		}
		first[k] = '\0';

		printf("temp %s\n",first);
		
		i ++;
		k = 0;
		j = 0;
	}

	printf("first %s\n",first);
	printf("sec %s\n",sec);

	return 0;
}
