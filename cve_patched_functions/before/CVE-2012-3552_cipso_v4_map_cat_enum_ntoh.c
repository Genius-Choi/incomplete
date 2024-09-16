static int cipso_v4_map_cat_enum_ntoh(const struct cipso_v4_doi *doi_def,
				      const unsigned char *net_cat,
				      u32 net_cat_len,
				      struct netlbl_lsm_secattr *secattr)
{
	int ret_val;
	u32 iter;

	for (iter = 0; iter < net_cat_len; iter += 2) {
		ret_val = netlbl_secattr_catmap_setbit(secattr->attr.mls.cat,
				get_unaligned_be16(&net_cat[iter]),
				GFP_ATOMIC);
		if (ret_val != 0)
			return ret_val;
	}

	return 0;
}
