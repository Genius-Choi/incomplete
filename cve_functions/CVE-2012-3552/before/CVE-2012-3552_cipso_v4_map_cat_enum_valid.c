static int cipso_v4_map_cat_enum_valid(const struct cipso_v4_doi *doi_def,
				       const unsigned char *enumcat,
				       u32 enumcat_len)
{
	u16 cat;
	int cat_prev = -1;
	u32 iter;

	if (doi_def->type != CIPSO_V4_MAP_PASS || enumcat_len & 0x01)
		return -EFAULT;

	for (iter = 0; iter < enumcat_len; iter += 2) {
		cat = get_unaligned_be16(&enumcat[iter]);
		if (cat <= cat_prev)
			return -EFAULT;
		cat_prev = cat;
	}

	return 0;
}
