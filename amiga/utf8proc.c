/* tmux's utf8proc hook (compat.h: utf8proc_wcwidth, utf8proc_mbtowc,
 * utf8proc_wctomb) on AmigaOS, where ixemul has no UTF-8 locale and no
 * wcwidth. The width is vtcon's (engine/vtwidth.h), so tmux lays its panes
 * out exactly as the XCON console draws them. The codec is strict UTF-8:
 * no overlong forms, no surrogates, nothing above U+10FFFF. */
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

typedef unsigned long vt_u32;
#include "vtwidth.h"


const char *
utf8proc_version(void)
{
	return ("none: the vtcon console's widths (UP-Term)");
}

int
utf8proc_wcwidth(wchar_t wc)
{
	if (wc < 0x20 || (wc >= 0x7f && wc < 0xa0))
		return (-1);	/* a control: no width, as wcwidth says */
	return (vt_char_width((vt_u32)wc));
}

int
utf8proc_mbtowc(wchar_t *pwc, const char *s, size_t n)
{
	const unsigned char *p = (const unsigned char *)s;
	unsigned long c, min;
	size_t len, i;

	if (s == NULL)
		return (0);
	if (n == 0)
		return (-1);
	if (p[0] < 0x80) {
		*pwc = p[0];
		return (p[0] != 0);
	}
	if ((p[0] & 0xe0) == 0xc0) {
		len = 2; c = p[0] & 0x1f; min = 0x80;
	} else if ((p[0] & 0xf0) == 0xe0) {
		len = 3; c = p[0] & 0x0f; min = 0x800;
	} else if ((p[0] & 0xf8) == 0xf0) {
		len = 4; c = p[0] & 0x07; min = 0x10000;
	} else
		return (-1);
	if (n < len)
		return (-1);
	for (i = 1; i < len; i++) {
		if ((p[i] & 0xc0) != 0x80)
			return (-1);
		c = (c << 6) | (p[i] & 0x3f);
	}
	if (c < min || c > 0x10ffff || (c >= 0xd800 && c <= 0xdfff))
		return (-1);
	*pwc = (wchar_t)c;
	return ((int)len);
}

int
utf8proc_wctomb(char *s, wchar_t wc)
{
	unsigned long c = (unsigned long)wc;

	if (s == NULL)
		return (0);
	if (c > 0x10ffff || (c >= 0xd800 && c <= 0xdfff))
		return (-1);
	if (c < 0x80) {
		s[0] = (char)c;
		return (1);
	}
	if (c < 0x800) {
		s[0] = (char)(0xc0 | (c >> 6));
		s[1] = (char)(0x80 | (c & 0x3f));
		return (2);
	}
	if (c < 0x10000) {
		s[0] = (char)(0xe0 | (c >> 12));
		s[1] = (char)(0x80 | ((c >> 6) & 0x3f));
		s[2] = (char)(0x80 | (c & 0x3f));
		return (3);
	}
	s[0] = (char)(0xf0 | (c >> 18));
	s[1] = (char)(0x80 | ((c >> 12) & 0x3f));
	s[2] = (char)(0x80 | ((c >> 6) & 0x3f));
	s[3] = (char)(0x80 | (c & 0x3f));
	return (4);
}
