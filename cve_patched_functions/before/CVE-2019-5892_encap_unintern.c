static void encap_unintern(struct bgp_attr_encap_subtlv **encapp,
			   encap_subtlv_type type)
{
	struct bgp_attr_encap_subtlv *encap = *encapp;
	if (encap->refcnt)
		encap->refcnt--;

	if (encap->refcnt == 0) {
		struct hash *hash = encap_hash;
#if ENABLE_BGP_VNC
		if (type == VNC_SUBTLV_TYPE)
			hash = vnc_hash;
#endif
		hash_release(hash, encap);
		encap_free(encap);
		*encapp = NULL;
	}
}
