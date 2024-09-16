void bgp_attr_finish(void)
{
	aspath_finish();
	attrhash_finish();
	community_finish();
	ecommunity_finish();
	lcommunity_finish();
	cluster_finish();
	transit_finish();
	encap_finish();
}
