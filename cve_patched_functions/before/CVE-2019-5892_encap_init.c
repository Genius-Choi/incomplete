static void encap_init(void)
{
	encap_hash = hash_create(encap_hash_key_make, encap_hash_cmp,
				 "BGP Encap Hash");
#if ENABLE_BGP_VNC
	vnc_hash = hash_create(encap_hash_key_make, encap_hash_cmp,
			       "BGP VNC Hash");
#endif
}
