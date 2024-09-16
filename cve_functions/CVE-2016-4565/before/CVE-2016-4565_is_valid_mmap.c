static inline int is_valid_mmap(u64 token)
{
	return (HFI1_MMAP_TOKEN_GET(MAGIC, token) == HFI1_MMAP_MAGIC);
}
