#include "pthread_impl.h"

int *__errno_location(void)
{
	static int _errno;
	struct pthread * ptr = __pthread_self();
	if (!ptr) {
		return &_errno;
	}
	return &ptr->errno_val;
}
