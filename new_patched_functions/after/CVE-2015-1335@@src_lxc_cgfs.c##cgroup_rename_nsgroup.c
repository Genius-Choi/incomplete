static char *cgroup_rename_nsgroup(const char *mountpath, const char *oldname, pid_t pid, const char *name)
{
	char *dir, *fulloldpath;
	char *newname, *fullnewpath;
	int len, newlen, ret;

	/*
	 * if cgroup is mounted at /cgroup and task is in cgroup /ab/, pid 2375 and
	 * name is c1,
	 * dir: /ab
	 * fulloldpath = /cgroup/ab/2375
	 * fullnewpath = /cgroup/ab/c1
	 * newname = /ab/c1
	 */
	dir = alloca(strlen(oldname) + 1);
	strcpy(dir, oldname);

	len = strlen(oldname) + strlen(mountpath) + 22;
	fulloldpath = alloca(len);
	ret = snprintf(fulloldpath, len, "%s/%s/%ld", mountpath, oldname, (unsigned long)pid);
	if (ret < 0 || ret >= len)
		return NULL;

	len = strlen(dir) + strlen(name) + 2;
	newname = malloc(len);
	if (!newname) {
		SYSERROR("Out of memory");
		return NULL;
	}
	ret = snprintf(newname, len, "%s/%s", dir, name);
	if (ret < 0 || ret >= len) {
		free(newname);
		return NULL;
	}

	newlen = strlen(mountpath) + len + 2;
	fullnewpath = alloca(newlen);
	ret = snprintf(fullnewpath, newlen, "%s/%s", mountpath, newname);
	if (ret < 0 || ret >= newlen) {
		free(newname);
		return NULL;
	}

	if (access(fullnewpath, F_OK) == 0) {
		if (rmdir(fullnewpath) != 0) {
			SYSERROR("container cgroup %s already exists.", fullnewpath);
			free(newname);
			return NULL;
		}
	}
	if (rename(fulloldpath, fullnewpath)) {
		SYSERROR("failed to rename cgroup %s->%s", fulloldpath, fullnewpath);
		free(newname);
		return NULL;
	}

	DEBUG("'%s' renamed to '%s'", oldname, newname);

	return newname;
}
