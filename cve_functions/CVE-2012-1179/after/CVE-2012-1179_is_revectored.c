static inline int is_revectored(int nr, struct revectored_struct *bitmap)
{
	__asm__ __volatile__("btl %2,%1\n\tsbbl %0,%0"
		:"=r" (nr)
		:"m" (*bitmap), "r" (nr));
	return nr;
}
