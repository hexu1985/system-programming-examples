/* 程序10-13 signal_intr函数 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

typedef void Sigfunc(int);

Sigfunc *signal_intr(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef	SA_INTERRUPT		/* SunOS */
	act.sa_flags |= SA_INTERRUPT;
#endif
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
