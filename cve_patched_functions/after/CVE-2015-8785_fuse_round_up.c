static inline loff_t fuse_round_up(loff_t off)
{
	return round_up(off, FUSE_MAX_PAGES_PER_REQ << PAGE_SHIFT);
}
