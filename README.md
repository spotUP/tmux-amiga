# tmux-amiga

tmux port for AmigaOS 3.x with ixemul, for the UP-Term kit. Part of the upterm source tree.

## Build

    make -f Makefile.amiga          # build/libevent.a, build/evprobe, build/tmux-bin

`build/tmux-bin` is what vtcon's `make dist` copies (`TMUX_BIN=`). The tmux
3.6a and libevent 2.1.12 sources are committed (`tmux/`, `libevent/`; the
release tarballs are gitignored and not needed); `amiga/` holds the
hand-written configuration.

Needs, all outside this repo:

- bebbo's gcc 6.5 in `~/opt/amiga` (`AGCC=`, `AAR=`), see upterm's `toolchain/README.md`.
- The ixemul SDK with `ixemul-vtcon`'s headers and `libixcompat.a` installed
  (`sh docker/install-sdk-headers.sh` and `make -C compat install` in ixemul-vtcon).
- Geek Gadgets ncurses 5.5 (Aminet `dev/gg/ncurses-5.5-1-bin-m68k`) unpacked at
  `$UPTERM_ROOT/vtcon/build/rig/vtc/pkgs/ncurses-5.5-1-p-bin-m68k` (`NCURSES=`).

`UPTERM_ROOT` (default: the parent of this repo) is the workspace directory; the
whole path from an empty Mac is in the `upterm` repo's README, "Set up the whole
thing". The test is `python3 tools/rig/tmux_rig.py` in vtcon (rig up).
