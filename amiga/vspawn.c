/* See vspawn.h. */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "vspawn.h"

extern char **environ;
void closefrom(int);

pid_t
amiga_vspawn(const struct amiga_child *c)
{
	char	**saved = environ;
	pid_t	  pid;

	pid = vfork();
	if (pid == 0) {
		struct termios	t;
		int		sig, i, fd;

		for (sig = 1; sig < NSIG; sig++)
			signal(sig, SIG_DFL);
		if (c->cwd != NULL && chdir(c->cwd) != 0)
			_exit(1);
		if (c->tty != NULL) {
			setsid();
			close(0);
			close(1);
			close(2);
			if (open(c->tty, O_RDWR) != 0)
				_exit(1);
			dup(0);
			dup(0);
#ifdef TIOCSCTTY
			ioctl(0, TIOCSCTTY, (char *)0);
#endif
			tcsetpgrp(0, getpid());
			if (tcgetattr(0, &t) == 0) {
				if (c->cc != NULL)
					memcpy(t.c_cc, c->cc, sizeof t.c_cc);
				if (c->verase >= 0)
					t.c_cc[VERASE] = c->verase;
				tcsetattr(0, TCSANOW, &t);
			}
		} else {
			for (i = 0; i < 3; i++) {
				if (c->fd[i] == -2) {
					fd = open("/dev/null", O_RDWR);
					if (fd >= 0 && fd != i) {
						dup2(fd, i);
						close(fd);
					}
				} else if (c->fd[i] >= 0 && c->fd[i] != i)
					dup2(c->fd[i], i);
			}
		}
		if (c->close_fd >= 0)
			close(c->close_fd);
		closefrom(3);
		sigprocmask(SIG_SETMASK, c->mask, NULL);
		/* shared with the parent until the exec, which copies it; the
		   parent puts its own back as soon as vfork returns there */
		environ = (char **)c->envp;
		if (c->use_path)
			execvp(c->path, c->argv);
		else
			execv(c->path, c->argv);
		_exit(127);
	}
	environ = saved;
	return (pid);
}

/* tmux opens no pty multiplexer device first (compat/fdforkpty.c's value) */
int
getptmfd(void)
{
	return (0x7fffffff);
}

int
amiga_openpty(int *master, char *name, size_t len)
{
	static const char c1[] = "pqrstu", c2[] = "0123456789abcdef";
	char	 m[16];
	int	 i, j, fd;

	for (i = 0; c1[i] != '\0'; i++) {
		for (j = 0; c2[j] != '\0'; j++) {
			snprintf(m, sizeof m, "/dev/pty%c%c", c1[i], c2[j]);
			if ((fd = open(m, O_RDWR)) == -1)
				continue;
			snprintf(name, len, "/dev/tty%c%c", c1[i], c2[j]);
			*master = fd;
			return (0);
		}
	}
	errno = EAGAIN;
	return (-1);
}
