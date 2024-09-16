static bool find_cgroup_subsystems(char ***kernel_subsystems)
{
	FILE *proc_cgroups;
	bool bret = false;
	char *line = NULL;
	size_t sz = 0;
	size_t kernel_subsystems_count = 0;
	size_t kernel_subsystems_capacity = 0;
	int r;

	proc_cgroups = fopen_cloexec("/proc/cgroups", "r");
	if (!proc_cgroups)
		return false;

	while (getline(&line, &sz, proc_cgroups) != -1) {
		char *tab1;
		char *tab2;
		int hierarchy_number;

		if (line[0] == '#')
			continue;
		if (!line[0])
			continue;

		tab1 = strchr(line, '\t');
		if (!tab1)
			continue;
		*tab1++ = '\0';
		tab2 = strchr(tab1, '\t');
		if (!tab2)
			continue;
		*tab2 = '\0';

		tab2 = NULL;
		hierarchy_number = strtoul(tab1, &tab2, 10);
		if (!tab2 || *tab2)
			continue;
		(void)hierarchy_number;

		r = lxc_grow_array((void ***)kernel_subsystems, &kernel_subsystems_capacity, kernel_subsystems_count + 1, 12);
		if (r < 0)
			goto out;
		(*kernel_subsystems)[kernel_subsystems_count] = strdup(line);
		if (!(*kernel_subsystems)[kernel_subsystems_count])
			goto out;
		kernel_subsystems_count++;
	}
	bret = true;

out:
	fclose(proc_cgroups);
	free(line);
	return bret;
}
