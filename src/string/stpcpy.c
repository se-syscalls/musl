#include "libc.h"

char * __stpcpy(char * to, const char * from)
{

	for (; (*to = *from); ++from, ++to);
	return(to);
}
weak_alias(__stpcpy, stpcpy);
