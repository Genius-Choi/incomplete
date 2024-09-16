static inline unsigned int unix_hash_fold(__wsum n)
{
	unsigned int hash = (__force unsigned int)n;

	hash ^= hash>>16;
	hash ^= hash>>8;
	return hash&(UNIX_HASH_SIZE-1);
}
