struct lxc_list *sort_cgroup_settings(struct lxc_list* cgroup_settings)
{
	struct lxc_list *result;
	struct lxc_list *memsw_limit = NULL;
	struct lxc_list *it = NULL;
	struct lxc_cgroup *cg = NULL;
	struct lxc_list *item = NULL;

	result = malloc(sizeof(*result));
	if (!result) {
		ERROR("failed to allocate memory to sort cgroup settings");
		return NULL;
	}
	lxc_list_init(result);

	/*Iterate over the cgroup settings and copy them to the output list*/
	lxc_list_for_each(it, cgroup_settings) {
		item = malloc(sizeof(*item));
		if (!item) {
			ERROR("failed to allocate memory to sort cgroup settings");
			free_cgroup_settings(result);
			return NULL;
		}
		item->elem = it->elem;
		cg = it->elem;
		if (strcmp(cg->subsystem, "memory.memsw.limit_in_bytes") == 0) {
			/* Store the memsw_limit location */
			memsw_limit = item;
		} else if (strcmp(cg->subsystem, "memory.limit_in_bytes") == 0 && memsw_limit != NULL) {
			/* lxc.cgroup.memory.memsw.limit_in_bytes is found before
			 * lxc.cgroup.memory.limit_in_bytes, swap these two items */
			item->elem = memsw_limit->elem;
			memsw_limit->elem = it->elem;
		}
		lxc_list_add_tail(result, item);
	}

	return result;
}
