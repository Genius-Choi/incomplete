static int fwnet_header_cache(const struct neighbour *neigh,
			      struct hh_cache *hh, __be16 type)
{
	struct net_device *net;
	struct fwnet_header *h;

	if (type == cpu_to_be16(ETH_P_802_3))
		return -1;
	net = neigh->dev;
	h = (struct fwnet_header *)((u8 *)hh->hh_data + HH_DATA_OFF(sizeof(*h)));
	h->h_proto = type;
	memcpy(h->h_dest, neigh->ha, net->addr_len);
	hh->hh_len = FWNET_HLEN;

	return 0;
}
