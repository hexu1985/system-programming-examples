/* 程序12-2 加锁和解锁一个文件区域的函数 */
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;		/* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset;	/* byet offset, relative to l_whence */
	lock.l_whence = whence;	/* SEEK_SET,  SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */

	return(fcntl(fd, cmd, &lock));
}
