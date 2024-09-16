bool get_mapped_rootid(struct lxc_conf *conf, enum idtype idtype,
			unsigned long *val)
{
	struct lxc_list *it;
	struct id_map *map;

	lxc_list_for_each(it, &conf->id_map) {
		map = it->elem;
		if (map->idtype != idtype)
			continue;
		if (map->nsid != 0)
			continue;
		*val = map->hostid;
		return true;
	}
	return false;
}
