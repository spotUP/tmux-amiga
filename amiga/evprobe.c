/* evprobe -- libevent on AmigaOS + ixemul (tmux port T2.1): one event
 * base, the select backend, a 200 ms timer, a read event on a socketpair
 * (tmux's client and server talk over one), and SIGCHLD when a vfork child
 * ends (tmux reaps its panes that way). Prints ok/FAIL per check. */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <event2/event.h>

static int timer_hits, read_bytes, sigchld_hits, write_hits, passed, total;
static struct event_base *base;

static void check(int ok, const char *what)
{
    total++;
    passed += ok != 0;
    printf("%s %d %s\n", ok ? "ok" : "FAIL", total, what);
}

static void on_timer(evutil_socket_t fd, short ev, void *arg)
{
    (void)fd; (void)ev; (void)arg;
    timer_hits++;
}

static void on_read(evutil_socket_t fd, short ev, void *arg)
{
    char buf[64];
    int n = read(fd, buf, sizeof buf);
    (void)ev; (void)arg;
    if (n > 0)
        read_bytes += n;
}

static void on_sigchld(evutil_socket_t sig, short ev, void *arg)
{
    int st;
    (void)sig; (void)ev; (void)arg;
    while (waitpid(-1, &st, WNOHANG) > 0)
        sigchld_hits++;
}

static void on_write(evutil_socket_t fd, short ev, void *arg)
{
    (void)ev; (void)arg;
    write(fd, "[write event]\n", 14);
    write_hits++;
}

static void on_done(evutil_socket_t fd, short ev, void *arg)
{
    (void)fd; (void)ev; (void)arg;
    event_base_loopbreak(base);
}

int main(void)
{
    struct event *t, *r, *s, *d;
    struct timeval tv200 = { 0, 200000 }, tv2s = { 2, 0 };
    int sv[2], pid;

    base = event_base_new();
    check(base != NULL, "event_base_new");
    if (!base)
        return 20;
    printf("backend: %s\n", event_base_get_method(base));
    check(!strcmp(event_base_get_method(base), "select"), "the select backend");

    t = event_new(base, -1, 0, on_timer, NULL);
    event_add(t, &tv200);
    check(socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == 0, "socketpair");
    r = event_new(base, sv[0], EV_READ | EV_PERSIST, on_read, NULL);
    event_add(r, NULL);
    s = evsignal_new(base, SIGCHLD, on_sigchld, NULL);
    event_add(s, NULL);
    d = event_new(base, -1, 0, on_done, NULL);
    event_add(d, &tv2s);

    {
        /* a write event on the terminal (tmux draws through one) */
        int tty = open("/dev/tty", O_RDWR);
        check(tty >= 0, "open /dev/tty");
        if (tty >= 0) {
            struct event *w = event_new(base, tty, EV_WRITE, on_write, NULL);
            event_add(w, NULL);
        }
    }
    write(sv[1], "hello", 5);
    pid = vfork();
    if (pid == 0)
        _exit(0);          /* SIGCHLD for the parent */

    event_base_dispatch(base);
    check(timer_hits == 1, "the 200 ms timer fired once");
    check(read_bytes == 5, "the socketpair read event got 5 bytes");
    check(sigchld_hits == 1, "SIGCHLD from the vfork child, reaped");
    check(write_hits == 1, "the write event on /dev/tty fired");
    printf("evprobe: passed %d of %d\n", passed, total);
    return passed == total ? 0 : 10;
}
