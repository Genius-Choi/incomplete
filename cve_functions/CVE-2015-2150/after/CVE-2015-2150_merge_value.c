static inline u32 merge_value(u32 val, u32 new_val, u32 new_val_mask,
			      int offset)
{
	if (offset >= 0) {
		new_val_mask <<= (offset * 8);
		new_val <<= (offset * 8);
	} else {
		new_val_mask >>= (offset * -8);
		new_val >>= (offset * -8);
	}
	val = (val & ~new_val_mask) | (new_val & new_val_mask);

	return val;
}
