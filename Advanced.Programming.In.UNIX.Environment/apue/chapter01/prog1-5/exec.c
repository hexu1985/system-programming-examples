/* 程序1-5 从标准输入读取命令并执行 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define	MAXLINE	4096

int main(void)
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%% ");	/* 打印提示符% */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		buf[strlen(buf)-1] = 0;		/* 将'\n'替换成'\0' */

		if ((pid=fork()) < 0) {
			fprintf(stderr, "fork error\n");
			exit(1);
		} else if (pid == 0) {	/* 子进程 */
			execlp(buf, buf, (char *) 0);	/* 如果执行成功，则不会返回，否则返回-1 */
			printf("%s无法执行\n", buf);
			exit(127);
		}

		/* 父进程 */
		if ((pid=waitpid(pid, &status, 0)) < 0) {
			fprintf(stderr, "waitpid error\n");
			exit(2);
		}

		printf("%% ");
	}

	exit(0);
}


