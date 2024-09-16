static void masked_increment(ulong *reg, ulong mask, int inc)
{
	assign_masked(reg, *reg + inc, mask);
}
