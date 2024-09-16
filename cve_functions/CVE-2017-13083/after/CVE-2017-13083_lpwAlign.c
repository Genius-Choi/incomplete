static __inline LPWORD lpwAlign(LPWORD addr)
{
	return (LPWORD)((((uintptr_t)addr) + 3) & (~3));
}
