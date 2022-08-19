# Digital UNIX 4.0 compilation flags:
CC=gcc
CFLAGS=-pthread -g -Wall $(DEBUGFLAGS)
RTFLAGS=-lrt

# Solaris 2.5 compilation flags:
#CFLAGS=-D_POSIX_C_SOURCE=199506 -D_REENTRANT -Xa -lpthread -g $(DEBUGFLAGS)
#RTFLAGS=-lposix4

SOURCES=alarm.c	alarm_cond.c	alarm_fork.c	alarm_mutex.c	\
	alarm_thread.c	atfork.c	backoff.c	\
	barrier_main.c	cancel.c	cancel_async.c	cancel_cleanup\
	cancel_disable.c cancel_subcontract.c	cond.c	cond_attr.c	\
	crew.c cond_dynamic.c	cond_static.c	flock.c	getlogin.c hello.c \
	inertia.c	lifecycle.c	mutex_attr.c	\
	mutex_dynamic.c	mutex_static.c	once.c	pipe.c	putchar.c	\
	rwlock_main.c	rwlock_try_main.c		\
	sched_attr.c	sched_thread.c	semaphore_signal.c	\
	semaphore_wait.c	server.c	sigev_thread.c	\
	sigwait.c	susp.c	thread.c \
	thread_attr.c	thread_error.c	trylock.c	tsd_destructor.c \
	tsd_once.c	workq_main.c pthread_rwlock_main.c
PROGRAMS=$(SOURCES:.c=)
all:	${PROGRAMS}
alarm_mutex: alarm_mutex.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
backoff: backoff.c 
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
sched_attr: sched_attr.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
sched_thread: sched_thread.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
semaphore_signal: semaphore_signal.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
semaphore_wait: semaphore_wait.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
sigev_thread: sigev_thread.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
susp: susp.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
rwlock_main: rwlock.c rwlock.h rwlock_main.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
rwlock_try_main: rwlock.h rwlock.c rwlock_try_main.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
barrier_main: barrier.h barrier.c barrier_main.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
workq_main: workq.h workq.c workq_main.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
pthread_rwlock_main: pthread_rwlock_main.c
	${CC} ${CFLAGS} -o $@ $^ ${RTFLAGS} ${LDFLAGS} 
clean:
	@rm -rf $(PROGRAMS) *.o
recompile:	clean all
