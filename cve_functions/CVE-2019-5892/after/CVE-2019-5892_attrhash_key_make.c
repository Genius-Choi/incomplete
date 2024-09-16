unsigned int attrhash_key_make(void *p)
{
	const struct attr *attr = (struct attr *)p;
	uint32_t key = 0;
#define MIX(val)	key = jhash_1word(val, key)
#define MIX3(a, b, c)	key = jhash_3words((a), (b), (c), key)

	MIX3(attr->origin, attr->nexthop.s_addr, attr->med);
	MIX3(attr->local_pref, attr->aggregator_as,
	     attr->aggregator_addr.s_addr);
	MIX3(attr->weight, attr->mp_nexthop_global_in.s_addr,
	     attr->originator_id.s_addr);
	MIX3(attr->tag, attr->label, attr->label_index);

	if (attr->aspath)
		MIX(aspath_key_make(attr->aspath));
	if (attr->community)
		MIX(community_hash_make(attr->community));

	if (attr->lcommunity)
		MIX(lcommunity_hash_make(attr->lcommunity));
	if (attr->ecommunity)
		MIX(ecommunity_hash_make(attr->ecommunity));
	if (attr->cluster)
		MIX(cluster_hash_key_make(attr->cluster));
	if (attr->transit)
		MIX(transit_hash_key_make(attr->transit));
	if (attr->encap_subtlvs)
		MIX(encap_hash_key_make(attr->encap_subtlvs));
#if ENABLE_BGP_VNC
	if (attr->vnc_subtlvs)
		MIX(encap_hash_key_make(attr->vnc_subtlvs));
#endif
	MIX(attr->mp_nexthop_len);
	key = jhash(attr->mp_nexthop_global.s6_addr, IPV6_MAX_BYTELEN, key);
	key = jhash(attr->mp_nexthop_local.s6_addr, IPV6_MAX_BYTELEN, key);
	MIX(attr->nh_ifindex);
	MIX(attr->nh_lla_ifindex);

	return key;
}
