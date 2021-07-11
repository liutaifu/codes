#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	int temp = 0;
	int *list = NULL;

	list = (int*)malloc(sizeof(int) * 1024);

	printf("请输入数组长度：");
	scanf("%d",&m);
	printf("请输入裁剪数组的变量：");
	scanf("%d",&n);

	printf("请输入数组的值：");
	for(i = 0; i < m; i ++) {
		scanf("%d", &(list[i]));
	}
	for(i = 0; i < m; i++) {
		printf("%3d ", list[i]);
	}
	for(i = 0; i < m; i++) {
		for(j = i + 1; j < m; j++) {
			if (list[i] > list[j]) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}

	if (n > m) {
		printf("n large num of list m\n");
	} else {
		printf("return n num of list\n");
	}
	for(i = 0; i < m; i++) {
		printf("%3d ", list[i]);
	}
	return 0;
}
