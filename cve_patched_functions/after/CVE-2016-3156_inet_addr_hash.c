static u32 inet_addr_hash(const struct net *net, __be32 addr)
{
	u32 val = (__force u32) addr ^ net_hash_mix(net);

	return hash_32(val, IN4_ADDR_HSIZE_SHIFT);
}
