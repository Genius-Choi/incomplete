static u32 fsflags_cvt(const u32 *table, u32 val)
{
	u32 res = 0;
	while(val) {
		if (val & 1)
			res |= *table;
		table++;
		val >>= 1;
	}
	return res;
}
