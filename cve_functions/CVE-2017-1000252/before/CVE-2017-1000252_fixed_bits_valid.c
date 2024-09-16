static inline bool fixed_bits_valid(u64 val, u64 fixed0, u64 fixed1)
{
	return ((val & fixed1) | fixed0) == val;
}
