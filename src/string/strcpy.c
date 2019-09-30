#include <string.h>

char *__stpcpy(char *, const char *);

char *strcpy(char *restrict dest, const char *restrict src)
{
#if 0
	__stpcpy(dest, src);
	return dest;
#else
	const char *s = src;
	char *d = dest;
	while ((*d++ = *s++));
	return dest;
#endif
}
