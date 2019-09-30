#include "pthread_impl.h"

extern int arch_prctl(int code, unsigned long addr);

struct pthread __pthread_arch_pthread_self_i = {0};
struct pthread * __pthread_arch_pthread_self_p = &__pthread_arch_pthread_self_i;

int __set_thread_area(void *p)
{
#ifdef SYS_arch_prctl
	__pthread_arch_pthread_self_p = p;
	return arch_prctl(0x1002, p);
#else
	return -ENOSYS;
#endif
}
