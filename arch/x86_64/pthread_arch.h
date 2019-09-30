
void abort(void);

extern struct pthread * __pthread_arch_pthread_self_p;
extern struct pthread __pthread_arch_pthread_self_i;

static inline struct pthread *__pthread_self()
{
	if (!__pthread_arch_pthread_self_p) {
		__pthread_arch_pthread_self_p = &__pthread_arch_pthread_self_i;
	}
	return __pthread_arch_pthread_self_p;
}

#define TP_ADJ(p) (p)

#define MC_PC gregs[REG_RIP]
