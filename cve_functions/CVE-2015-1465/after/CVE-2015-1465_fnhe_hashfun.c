static inline u32 fnhe_hashfun(__be32 daddr)
{
	static u32 fnhe_hashrnd __read_mostly;
	u32 hval;

	net_get_random_once(&fnhe_hashrnd, sizeof(fnhe_hashrnd));
	hval = jhash_1word((__force u32) daddr, fnhe_hashrnd);
	return hash_32(hval, FNHE_HASH_SHIFT);
}
