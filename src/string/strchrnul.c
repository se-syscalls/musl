#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "libc.h"

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

char *__strchrnul(const char *s, int c)
{
	size_t *w, k;

	c = (unsigned char)c;
	if (!c) return (char *)s + strlen(s);
	for (; *s; s++) {
		if (*s == c) {
			break;
		}
	}
	return (char*)s;
}

weak_alias(__strchrnul, strchrnul);
