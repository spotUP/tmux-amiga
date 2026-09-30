/* libevent 2.1.12 on AmigaOS 3.x + ixemul 48.2 (UP-Term), written by hand
 * for bebbo's m68k-amigaos-gcc -mcrt=ixemul: libevent's configure does
 * not run for this target. One backend: select() (ixemul's select covers
 * sockets, pipes and PTY:/XCON: through their WAIT_CHAR packets). No
 * threads, no OpenSSL, no IPv6. Every HAVE_ below was checked against
 * the ixemul SDK headers (~/opt/amiga/m68k-amigaos/ixemul/include). */
#ifndef EVENT2_EVENT_CONFIG_H_INCLUDED_
#define EVENT2_EVENT_CONFIG_H_INCLUDED_

#define EVENT__NUMERIC_VERSION 0x02010c00
#define EVENT__VERSION "2.1.12-stable"
#define EVENT__PACKAGE_VERSION "2.1.12-stable"

#define EVENT__DISABLE_THREAD_SUPPORT 1
#define EVENT__DISABLE_DEBUG_MODE 1
#define EVENT__DISABLE_MM_REPLACEMENT 1

#define EVENT__HAVE_SELECT 1
#define EVENT__HAVE_SYS_SELECT_H_NOT 1

#define EVENT__HAVE_ERRNO_H 1
#define EVENT__HAVE_FCNTL_H 1
#define EVENT__HAVE_INTTYPES_H 1
#define EVENT__HAVE_NETDB_H 1
#define EVENT__HAVE_NETINET_IN_H 1
#define EVENT__HAVE_ARPA_INET_H 1
#define EVENT__HAVE_STDDEF_H 1
#define EVENT__HAVE_STDINT_H 1
#define EVENT__HAVE_STDLIB_H 1
#define EVENT__HAVE_STRING_H 1
#define EVENT__HAVE_SYS_IOCTL_H 1
#define EVENT__HAVE_SYS_PARAM_H 1
#define EVENT__HAVE_SYS_SOCKET_H 1
#define EVENT__HAVE_SYS_STAT_H 1
#define EVENT__HAVE_SYS_TIME_H 1
#define EVENT__HAVE_SYS_TYPES_H 1
#define EVENT__HAVE_SYS_UIO_H 1
#define EVENT__HAVE_UNISTD_H 1

#define EVENT__HAVE_FCNTL 1
#define EVENT__HAVE_GETTIMEOFDAY 1
#define EVENT__HAVE_SIGACTION 1
#define EVENT__HAVE_SIGNAL 1
#define EVENT__HAVE_STRSEP 1
#define EVENT__HAVE_STRTOK_R 1
#define EVENT__HAVE_PUTENV 1
#define EVENT__HAVE_SETENV 1
#define EVENT__HAVE_UNSETENV 1
#define EVENT__HAVE_GETHOSTBYNAME 1
#define EVENT__HAVE_INET_NTOA 1
#define EVENT__HAVE_TIMERADD 1
#define EVENT__HAVE_TIMERCLEAR 1
#define EVENT__HAVE_TIMERCMP 1
#define EVENT__HAVE_TIMERISSET 1
#define EVENT__HAVE_SETFD 1
#define EVENT__HAVE_FD_MASK 1
#define EVENT__HAVE_USLEEP 1

#define EVENT__HAVE_UINT8_T 1
#define EVENT__HAVE_UINT16_T 1
#define EVENT__HAVE_UINT32_T 1
#define EVENT__HAVE_UINT64_T 1
#define EVENT__HAVE_UINTPTR_T 1
#define EVENT__HAVE_SA_FAMILY_T 1

#define EVENT__SIZEOF_INT 4
#define EVENT__SIZEOF_LONG 4
#define EVENT__SIZEOF_LONG_LONG 8
#define EVENT__SIZEOF_OFF_T 4
#define EVENT__SIZEOF_SHORT 2
#define EVENT__SIZEOF_SIZE_T 4
#define EVENT__SIZEOF_VOID_P 4
#define EVENT__SIZEOF_PTHREAD_T 4
#define EVENT__SIZEOF_TIME_T 4

#define EVENT__HAVE___func__ 1
#define EVENT__HAVE___FUNCTION__ 1

#define EVENT__inline inline
#define EVENT____func__ __func__

#endif
