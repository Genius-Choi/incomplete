static int cipso_v4_map_lvl_ntoh(const struct cipso_v4_doi *doi_def,
				 u32 net_lvl,
				 u32 *host_lvl)
{
	struct cipso_v4_std_map_tbl *map_tbl;

	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		*host_lvl = net_lvl;
		return 0;
	case CIPSO_V4_MAP_TRANS:
		map_tbl = doi_def->map.std;
		if (net_lvl < map_tbl->lvl.cipso_size &&
		    map_tbl->lvl.cipso[net_lvl] < CIPSO_V4_INV_LVL) {
			*host_lvl = doi_def->map.std->lvl.cipso[net_lvl];
			return 0;
		}
		return -EPERM;
	}

	return -EINVAL;
}
