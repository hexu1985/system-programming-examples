/* 程序10-3 不能正常工作的系统V SIGCLD处理程序 */
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

static void sig_cld(int);

int main()
{
	pid_t pid;

	if (signal(SIGCLD, sig_cld) == (void (*)())-1) {
		perror("signal error");
		exit(1);
	}

	if ((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	} else if (pid == 0) {		/* child */
		sleep(2);
		_exit(0);
	}
	pause();	/* parent */
	exit(0);
}

static void sig_cld(int signo)
{
	pid_t pid;
	int status;

	printf("SIGCLD recived\n");
	if (signal(SIGCLD, sig_cld) == (void (*)())-1)		/* reestablish handler */
		perror("signal error");

	if ((pid = wait(&status)) < 0)			/* fetch child status */
		perror("wait error");
	printf("pid = %d\n", pid);
	return;						/* interrupts pause() */
}

