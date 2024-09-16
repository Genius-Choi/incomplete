int lxc_clear_cgroups(struct lxc_conf *c, const char *key)
{
	struct lxc_list *it,*next;
	bool all = false;
	const char *k = key + 11;

	if (strcmp(key, "lxc.cgroup") == 0)
		all = true;

	lxc_list_for_each_safe(it, &c->cgroup, next) {
		struct lxc_cgroup *cg = it->elem;
		if (!all && strcmp(cg->subsystem, k) != 0)
			continue;
		lxc_list_del(it);
		free(cg->subsystem);
		free(cg->value);
		free(cg);
		free(it);
	}
	return 0;
}
