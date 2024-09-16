static inline u8 fr_lmi_nextseq(u8 x)
{
	x++;
	return x ? x : 1;
}
