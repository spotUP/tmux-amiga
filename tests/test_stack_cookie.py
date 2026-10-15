#!/usr/bin/env python3
"""tmux on the rig hung at its first command with ixemul's "free: start of block corrupt!" / "realloc: start of
block corrupt!" requesters (resize_rig.py tmux, 3 of 3, 2026-10-15): tmux-bin carried no $STACK cookie, so vsh
(shell/vsh.c command_stack: the cookie, else the Shell's Stack, at least 16000) started it on 16000 bytes, and the
server and pane processes ixemul's vfork makes inherit that. tmux overflowed it and wrote over malloc's block headers
below the stack. The same case under `Stack 262144` (the window's Shell, so only the commands vsh starts) ran.

The fix: amiga/stack.c puts "$STACK: 262144" in the binary, the size vsh asks for itself; vsh, the AmigaOS 3.2 Shell
and Workbench read it. This test reads the built binary: the cookie is there and at least MIN bytes."""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BIN = os.path.join(ROOT, 'build', 'tmux-bin')
MIN = 262144


def main():
    data = open(BIN, 'rb').read()
    m = re.search(rb'\$STACK: ?(\d+)', data)
    fails = []
    if not m:
        fails.append('tmux overflows the 16000-byte stack vsh gives it: build/tmux-bin holds no $STACK cookie')
    elif int(m.group(1)) < MIN:
        fails.append('build/tmux-bin asks for %s bytes of stack, below %d' % (m.group(1).decode(), MIN))
    for f in fails:
        print('[FAIL] ' + f)
    print('stack_cookie: %d failed' % len(fails))
    sys.exit(1 if fails else 0)


main()
