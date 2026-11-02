/* See vspawn.h. Kept apart from vspawn.c: the NDK's devices/timer.h (pulled
 * in by proto/dos.h) and ixemul's sys/time.h both define struct timeval. */
#include <dos/dosextens.h>
#include <proto/dos.h>

#include "vspawn.h"

long ix_filehandle(int);

void
amiga_console_from_fd(int fd)
{
	BPTR	fh;

	if ((fh = (BPTR)ix_filehandle(fd)) != 0)
		SetConsoleTask(((struct FileHandle *)BADDR(fh))->fh_Type);
}
