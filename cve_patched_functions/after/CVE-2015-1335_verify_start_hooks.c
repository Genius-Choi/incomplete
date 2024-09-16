static bool verify_start_hooks(struct lxc_conf *conf)
{
	struct lxc_list *it;
	char path[MAXPATHLEN];
	lxc_list_for_each(it, &conf->hooks[LXCHOOK_START]) {
		char *hookname = it->elem;
		struct stat st;
		int ret;

		ret = snprintf(path, MAXPATHLEN, "%s%s",
			conf->rootfs.path ? conf->rootfs.mount : "", hookname);
		if (ret < 0 || ret >= MAXPATHLEN)
			return false;
		ret = stat(path, &st);
		if (ret) {
			SYSERROR("Start hook %s not found in container",
					hookname);
			return false;
		}
		return true;
	}

	return true;
}
