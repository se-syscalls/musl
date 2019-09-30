/* For klee, take everything from the C implementation */

#define a_cas a_cas
// Forgo this locking primitive for klee
static inline int a_cas(volatile int *p, int t, int s)
{
	int old = *p;
	if (old == t) {
		*p = s;
	}
	return old;
}

#define a_cas_p a_cas_p
// Forgo this locking primitive for klee
static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	volatile unsigned long * pp = p;
	unsigned long old = *pp;
	if (old == (unsigned long)t) {
		*pp = (unsigned long)s;
	}
	return (void*)old;
}
