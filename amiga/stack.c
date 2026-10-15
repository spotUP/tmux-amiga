/* The stack tmux asks for: vsh (shell/vsh.c command_stack), the AmigaOS 3.2
 * Shell and Workbench read this cookie from the file; without it vsh starts
 * tmux on 16000 bytes, the server and pane processes ixemul's vfork makes
 * inherit that, and tmux overflowed it into malloc's block headers (ixemul's
 * "free: start of block corrupt!", rig 2, 2026-10-15). 262144 is what vsh
 * asks for itself. tests/test_stack_cookie.py reads it from the binary. */
__attribute__((used)) const char amiga_stack_cookie[] = "$STACK: 262144";
