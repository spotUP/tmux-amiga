/* amiga_vspawn: tmux's children (panes, jobs, pipe-pane) on AmigaOS, which
 * has no fork(). vfork + exec: until its exec the child shares tmux's data
 * and heap, so everything it needs is prepared by the caller (argv, envp,
 * the directory, the pty's name) and the child only changes what is its
 * own -- descriptors, session and controlling tty, tty modes, signals. */
#ifndef AMIGA_VSPAWN_H
#define AMIGA_VSPAWN_H

#include <sys/types.h>
#include <signal.h>
#include <termios.h>

struct amiga_child {
	const char	 *path;		/* the program; searched in PATH when use_path */
	char *const	 *argv;
	char *const	 *envp;		/* its whole environment */
	int		  use_path;
	const char	 *cwd;		/* chdir to it (NULL: stay) */
	const char	 *tty;		/* a pane: the pty slave's name. The child starts a
					   session, the slave becomes 0, 1, 2 and its
					   controlling terminal */
	const cc_t	 *cc;		/* with tty: these c_cc (NCCS of them; NULL: keep) */
	int		  verase;	/* with tty: VERASE (-1: keep) */
	int		  fd[3];	/* without tty: onto 0, 1, 2 (-1: leave, -2: /dev/null) */
	int		  close_fd;	/* the parent's end, closed in the child (-1: none) */
	const sigset_t	 *mask;		/* the signal mask for the program */
};

/* The child's pid, or -1 with errno set. */
pid_t	amiga_vspawn(const struct amiga_child *);

/* A free pty pair (BSD names /dev/ptyXY, /dev/ttyXY on vtcon's PTY:): the
 * master open read/write, the slave's name in name (TTY_NAME_MAX). */
int	amiga_openpty(int *master, char *name, size_t len);

#endif
