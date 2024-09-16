int lxc_clear_hooks(struct lxc_conf *c, const char *key)
{
	struct lxc_list *it,*next;
	bool all = false, done = false;
	const char *k = key + 9;
	int i;

	if (strcmp(key, "lxc.hook") == 0)
		all = true;

	for (i=0; i<NUM_LXC_HOOKS; i++) {
		if (all || strcmp(k, lxchook_names[i]) == 0) {
			lxc_list_for_each_safe(it, &c->hooks[i], next) {
				lxc_list_del(it);
				free(it->elem);
				free(it);
			}
			done = true;
		}
	}

	if (!done) {
		ERROR("Invalid hook key: %s", key);
		return -1;
	}
	return 0;
}
