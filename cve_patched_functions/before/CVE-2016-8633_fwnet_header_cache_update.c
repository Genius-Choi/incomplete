static void fwnet_header_cache_update(struct hh_cache *hh,
		const struct net_device *net, const unsigned char *haddr)
{
	memcpy((u8 *)hh->hh_data + HH_DATA_OFF(FWNET_HLEN), haddr, net->addr_len);
}
