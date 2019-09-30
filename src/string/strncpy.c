#include <string.h>

char *__stpncpy(char *, const char *, size_t);

char *strncpy(char *restrict dest, const char *restrict src, size_t n)
{
#if 0
	__stpncpy(d, s, n);
	return d;
#else
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';
	return dest;
#endif
}
