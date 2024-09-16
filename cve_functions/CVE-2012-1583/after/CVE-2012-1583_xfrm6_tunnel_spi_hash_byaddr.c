static inline unsigned xfrm6_tunnel_spi_hash_byaddr(xfrm_address_t *addr)
{
	unsigned h;

	h = (__force u32)(addr->a6[0] ^ addr->a6[1] ^ addr->a6[2] ^ addr->a6[3]);
	h ^= h >> 16;
	h ^= h >> 8;
	h &= XFRM6_TUNNEL_SPI_BYADDR_HSIZE - 1;

	return h;
}
