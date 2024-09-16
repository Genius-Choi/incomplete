int ttys_shift_ids(struct lxc_conf *c)
{
	if (lxc_list_empty(&c->id_map))
		return 0;

	if (strcmp(c->console.name, "") !=0 && chown_mapped_root(c->console.name, c) < 0) {
		ERROR("Failed to chown %s", c->console.name);
		return -1;
	}

	return 0;
}
