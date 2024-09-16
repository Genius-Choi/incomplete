static int do_setup_cgroup_limits(struct cgfs_data *d,
			   struct lxc_list *cgroup_settings, bool do_devices)
{
	struct lxc_list *iterator, *sorted_cgroup_settings, *next;
	struct lxc_cgroup *cg;
	int ret = -1;

	if (lxc_list_empty(cgroup_settings))
		return 0;

	sorted_cgroup_settings = sort_cgroup_settings(cgroup_settings);
	if (!sorted_cgroup_settings) {
		return -1;
	}

	lxc_list_for_each(iterator, sorted_cgroup_settings) {
		cg = iterator->elem;

		if (do_devices == !strncmp("devices", cg->subsystem, 7)) {
			if (strcmp(cg->subsystem, "devices.deny") == 0 &&
					cgroup_devices_has_allow_or_deny(d, cg->value, false))
				continue;
			if (strcmp(cg->subsystem, "devices.allow") == 0 &&
					cgroup_devices_has_allow_or_deny(d, cg->value, true))
				continue;
			if (lxc_cgroup_set_data(cg->subsystem, cg->value, d)) {
				ERROR("Error setting %s to %s for %s",
				      cg->subsystem, cg->value, d->name);
				goto out;
			}
		}

		DEBUG("cgroup '%s' set to '%s'", cg->subsystem, cg->value);
	}

	ret = 0;
	INFO("cgroup has been setup");
out:
	lxc_list_for_each_safe(iterator, sorted_cgroup_settings, next) {
		lxc_list_del(iterator);
		free(iterator);
	}
	free(sorted_cgroup_settings);
	return ret;
}
