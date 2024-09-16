int find_unmapped_nsuid(struct lxc_conf *conf, enum idtype idtype)
{
	struct lxc_list *it;
	struct id_map *map;
	unsigned int freeid = 0;
again:
	lxc_list_for_each(it, &conf->id_map) {
		map = it->elem;
		if (map->idtype != idtype)
			continue;
		if (freeid >= map->nsid && freeid < map->nsid + map->range) {
			freeid = map->nsid + map->range;
			goto again;
		}
	}
	return freeid;
}
