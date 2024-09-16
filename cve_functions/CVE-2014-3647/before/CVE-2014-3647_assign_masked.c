static void assign_masked(ulong *dest, ulong src, ulong mask)
{
	*dest = (*dest & ~mask) | (src & mask);
}
