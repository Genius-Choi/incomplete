static int cipso_v4_map_lvl_hton(const struct cipso_v4_doi *doi_def,
				 u32 host_lvl,
				 u32 *net_lvl)
{
	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		*net_lvl = host_lvl;
		return 0;
	case CIPSO_V4_MAP_TRANS:
		if (host_lvl < doi_def->map.std->lvl.local_size &&
		    doi_def->map.std->lvl.local[host_lvl] < CIPSO_V4_INV_LVL) {
			*net_lvl = doi_def->map.std->lvl.local[host_lvl];
			return 0;
		}
		return -EPERM;
	}

	return -EINVAL;
}
