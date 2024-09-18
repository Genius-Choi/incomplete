static int cipso_v4_map_cat_enum_hton(const struct cipso_v4_doi *doi_def,
				      const struct netlbl_lsm_secattr *secattr,
				      unsigned char *net_cat,
				      u32 net_cat_len)
{
	int cat = -1;
	u32 cat_iter = 0;

	for (;;) {
		cat = netlbl_secattr_catmap_walk(secattr->attr.mls.cat,
						 cat + 1);
		if (cat < 0)
			break;
		if ((cat_iter + 2) > net_cat_len)
			return -ENOSPC;

		*((__be16 *)&net_cat[cat_iter]) = htons(cat);
		cat_iter += 2;
	}

	return cat_iter;
}
