static int cipso_v4_gentag_enum(const struct cipso_v4_doi *doi_def,
				const struct netlbl_lsm_secattr *secattr,
				unsigned char *buffer,
				u32 buffer_len)
{
	int ret_val;
	u32 tag_len;
	u32 level;

	if (!(secattr->flags & NETLBL_SECATTR_MLS_LVL))
		return -EPERM;

	ret_val = cipso_v4_map_lvl_hton(doi_def,
					secattr->attr.mls.lvl,
					&level);
	if (ret_val != 0)
		return ret_val;

	if (secattr->flags & NETLBL_SECATTR_MLS_CAT) {
		ret_val = cipso_v4_map_cat_enum_hton(doi_def,
						     secattr,
						     &buffer[4],
						     buffer_len - 4);
		if (ret_val < 0)
			return ret_val;

		tag_len = 4 + ret_val;
	} else
		tag_len = 4;

	buffer[0] = CIPSO_V4_TAG_ENUM;
	buffer[1] = tag_len;
	buffer[3] = level;

	return tag_len;
}
