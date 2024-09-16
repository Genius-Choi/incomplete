encap_intern(struct bgp_attr_encap_subtlv *encap, encap_subtlv_type type)
{
	struct bgp_attr_encap_subtlv *find;
	struct hash *hash = encap_hash;
#if ENABLE_BGP_VNC
	if (type == VNC_SUBTLV_TYPE)
		hash = vnc_hash;
#endif

	find = hash_get(hash, encap, encap_hash_alloc);
	if (find != encap)
		encap_free(encap);
	find->refcnt++;

	return find;
}
