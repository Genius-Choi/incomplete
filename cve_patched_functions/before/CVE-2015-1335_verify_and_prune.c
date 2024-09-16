static bool verify_and_prune(const char *cgroup_use)
{
	const char *p;
	char *e;
	int i, j;

	for (p = cgroup_use; p && *p; p = e + 1) {
		e = strchr(p, ',');
		if (e)
			*e = '\0';

		if (!in_subsystem_list(p)) {
			ERROR("Controller %s required by lxc.cgroup.use but not available\n", p);
			return false;
		}

		if (e)
			*e = ',';
		if (!e)
			break;
	}

	for (i = 0; i < nr_subsystems;) {
		if (in_comma_list(subsystems[i], cgroup_use)) {
			i++;
			continue;
		}
		free(subsystems[i]);
		for (j = i;  j < nr_subsystems-1; j++)
			subsystems[j] = subsystems[j+1];
		subsystems[nr_subsystems-1] = NULL;
		nr_subsystems--;
	}

	return true;
}
