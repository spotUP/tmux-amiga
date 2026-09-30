/* tmux 3.6a on AmigaOS 3.x + ixemul 48.2 (UP-Term), written by hand for
 * bebbo's m68k-amigaos-gcc -mcrt=ixemul (configure does not run for m68k).
 * A HAVE_ is set only for what the ixemul SDK has (its libc.a symbols and
 * headers, checked with m68k-amigaos-nm); everything else comes from
 * tmux's compat/. UTF-8: tmux's utf8proc hook, served by amiga/utf8proc.c
 * with vtcon's own width table (engine/vtwidth.h). */
#define PACKAGE "tmux"
#define PACKAGE_VERSION "3.6a"
#define VERSION "3.6a"
#define TMUX_VERSION "3.6a (UP-Term)"
#define TMUX_CONF "/ENV/tmux.conf:~/.tmux.conf:~/.config/tmux/tmux.conf"
#define TMUX_SOCK "/T"
#define TMUX_TERM "screen-256color"
#define TMUX_LOCK_CMD "lock -np"

/* headers */
#define HAVE_DIRENT_H 1
#define HAVE_FCNTL_H 1
#define HAVE_NCURSES_H 1
#define HAVE_PATHS_H 1
#define HAVE_STDINT_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_EVENT2_EVENT_H 1

/* functions in ixemul's libc */
#define HAVE_CFMAKERAW 1
#define HAVE_FGETLN 1
#define HAVE_FLOCK 1
#define HAVE_GETDTABLESIZE 1
#define HAVE_SETENV 1
#define HAVE_STRSEP 1
#define HAVE_SYSCONF 1

/* UTF-8 without a system locale: amiga/utf8proc.c */
#define HAVE_UTF8PROC 1

/* AmigaOS: no fork -- the server and panes start with vfork + exec */
#define TMUX_AMIGA 1
