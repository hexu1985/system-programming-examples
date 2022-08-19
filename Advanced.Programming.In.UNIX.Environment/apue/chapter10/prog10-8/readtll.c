/* 程序10-8 使用longjmp, 带时间限制调用read */
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define MAXLINE 4096

static void  sig_alrm(int);
static jmp_buf env_alrm;

int main(void)
{
	int n;
	char line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		perror("signal(SIGALRM) error");
		exit(1);
	}

	if (setjmp(env_alrm) != 0) {
		perror("read timeout");
		exit(1);
	}

	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
		perror("read error");
		exit(1);
	}
	alarm(0);

	write(STDOUT_FILENO, line, n);

	exit(0);
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}
