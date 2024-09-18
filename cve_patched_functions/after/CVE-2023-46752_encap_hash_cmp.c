static bool encap_hash_cmp(const void *p1, const void *p2)
{
	return encap_same((const struct bgp_attr_encap_subtlv *)p1,
			  (const struct bgp_attr_encap_subtlv *)p2);
}
