static const char *cgfs_canonical_path(void *hdata)
{
	struct cgfs_data *d = hdata;
	struct cgroup_process_info *info_ptr;
	char *path = NULL;

	if (!d)
		return NULL;

	for (info_ptr = d->info; info_ptr; info_ptr = info_ptr->next) {
		if (!path)
			path = info_ptr->cgroup_path;
		else if (strcmp(path, info_ptr->cgroup_path) != 0) {
			ERROR("not all paths match %s, %s has path %s", path,
				info_ptr->hierarchy->subsystems[0], info_ptr->cgroup_path);
			return NULL;
		}
	}

	return path;
}
