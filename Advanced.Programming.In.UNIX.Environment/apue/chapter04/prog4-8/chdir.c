/* 程序4-8 chdir函数实例 */
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	if (chdir("/tmp") < 0) {
		perror("chdir failed\n");
		exit(1);
	}

	printf("chdir to /tmp succeeded\n");
	exit(0);
}
