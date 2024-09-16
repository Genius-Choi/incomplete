int mapped_hostid(unsigned id, struct lxc_conf *conf, enum idtype idtype)
{
	struct lxc_list *it;
	struct id_map *map;
	lxc_list_for_each(it, &conf->id_map) {
		map = it->elem;
		if (map->idtype != idtype)
			continue;
		if (id >= map->hostid && id < map->hostid + map->range)
			return (id - map->hostid) + map->nsid;
	}
	return -1;
}
