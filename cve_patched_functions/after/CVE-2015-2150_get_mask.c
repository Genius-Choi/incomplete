static inline u32 get_mask(int size)
{
	if (size == 1)
		return 0xff;
	else if (size == 2)
		return 0xffff;
	else
		return 0xffffffff;
}
