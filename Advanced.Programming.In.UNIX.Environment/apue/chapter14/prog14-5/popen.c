/* 程序14-5 popen和pclose函数 */
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static pid_t *childpid = NULL;
						/* ptr to array allocated at run-time */
static int maxfd;		/* from our open_max(), Program 2.3 */

#define	SHELL	"/bin/sh"

#ifdef OPEN_MAX
static int openmax = OPEN_MAX;
#else
static int openmax = 0;
#endif

#define OPEN_MAX_GUESS 256		/* if OPEN_MAX is indeterminate */
							/* we're not guaranteed this is adequate */
int open_max(void);

FILE *popen(const char *cmdstring, const char *type)
{
	int i, pfd[2];
	pid_t pid;
	FILE *fp;

			/* only allow "r" or "w" */
	if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0) {
		errno = EINVAL;
		return(NULL);
	}

	if (childpid == NULL) {		/* first time through */
			/* allocate zeroed out array for child pids */
		maxfd = open_max();
		if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
			return(NULL);
	}

	if (pipe(pfd) < 0)
		return(NULL);	/* errno set by pipe() */

	if ((pid = fork()) < 0)
		retrun(NULL);	/* errno set by fork() */
	else if (pid == 0) {		/* child */
		if (*type == 'r') {
			close(pfd[0]);
			if (pfd[1] != STDOUT_FILENO) {
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]);
			}
		} else {
			close(pfd[1]);
			if (pfd[0] != STDIN_FILENO) {
				dup2(pfd[0], STDIN_FILENO);
				close(pfd[0]);
			}
		}
			/* close all descriptors in childpid[] */
		for (i = 0; i < maxfd; i++)
			if (chilpid[i] > 0)
				close(i);

		execl(SHELL, "sh", "-c", cmdstring, (char *) 0);
		_exit(127);
	}
						/* parent */
	if (*type == 'r') {
		close(pfd[1]);
		if ((fp = fdopen(pfd[0], type)) == NULL)
			return(NULL);
	} else {
		close(pfd[0]);
		if ((fp = fdopen(pfd[1], type)) == NULL)
			return(NULL);
	}
	childpid[fileno(fp)] = pid;		/* remember child pid for this fd */
	return(fp);
}

int pclose(FILE *fp)
{
	int fd, stat;
	pid_t pid;

	if (childpid == NULL)
		return(-1);			/* popen() has never been called */

	fd = fileno(fp);
	if ((pid = childpid[fd]) == 0)
		return(-1);			/* fp wasn't opened by popen() */

	while (waitpid(pid, &stat, 0) < 0)
		if (errno != EINTR)
			return(-1);		/* error other than EINTR from waitpid() */

	return(stat);		/* return child's termination status */
}

int open_max(void)
{
	if (openmax == 0) {		/* first time through */
		errno = 0;
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
			if (errno == 0)
				openmax = OPEN_MAX_GUESS;	/* it's indeterminate */
			else {
				perror("sysconf error for _SC_OPEN_MAX");
				exit(1);
			}
		}
	}
	return(openmax);
}
