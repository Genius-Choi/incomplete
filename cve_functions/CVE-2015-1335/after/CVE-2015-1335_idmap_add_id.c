static struct lxc_list *idmap_add_id(struct lxc_conf *conf,
		uid_t uid, gid_t gid)
{
	int hostuid_mapped = mapped_hostid(uid, conf, ID_TYPE_UID);
	int hostgid_mapped = mapped_hostid(gid, conf, ID_TYPE_GID);
	struct lxc_list *new = NULL, *tmp, *it, *next;
	struct id_map *entry;

	new = malloc(sizeof(*new));
	if (!new) {
		ERROR("Out of memory building id map");
		return NULL;
	}
	lxc_list_init(new);

	if (hostuid_mapped < 0) {
		hostuid_mapped = find_unmapped_nsuid(conf, ID_TYPE_UID);
		if (hostuid_mapped < 0)
			goto err;
		tmp = malloc(sizeof(*tmp));
		if (!tmp)
			goto err;
		entry = malloc(sizeof(*entry));
		if (!entry) {
			free(tmp);
			goto err;
		}
		tmp->elem = entry;
		entry->idtype = ID_TYPE_UID;
		entry->nsid = hostuid_mapped;
		entry->hostid = (unsigned long) uid;
		entry->range = 1;
		lxc_list_add_tail(new, tmp);
	}
	if (hostgid_mapped < 0) {
		hostgid_mapped = find_unmapped_nsuid(conf, ID_TYPE_GID);
		if (hostgid_mapped < 0)
			goto err;
		tmp = malloc(sizeof(*tmp));
		if (!tmp)
			goto err;
		entry = malloc(sizeof(*entry));
		if (!entry) {
			free(tmp);
			goto err;
		}
		tmp->elem = entry;
		entry->idtype = ID_TYPE_GID;
		entry->nsid = hostgid_mapped;
		entry->hostid = (unsigned long) gid;
		entry->range = 1;
		lxc_list_add_tail(new, tmp);
	}
	lxc_list_for_each_safe(it, &conf->id_map, next) {
		tmp = malloc(sizeof(*tmp));
		if (!tmp)
			goto err;
		entry = malloc(sizeof(*entry));
		if (!entry) {
			free(tmp);
			goto err;
		}
		memset(entry, 0, sizeof(*entry));
		memcpy(entry, it->elem, sizeof(*entry));
		tmp->elem = entry;
		lxc_list_add_tail(new, tmp);
	}

	return new;

err:
	ERROR("Out of memory building a new uid/gid map");
	if (new)
		lxc_free_idmap(new);
	free(new);
	return NULL;
}
