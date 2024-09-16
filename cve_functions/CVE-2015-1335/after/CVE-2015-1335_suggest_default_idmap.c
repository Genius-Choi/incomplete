void suggest_default_idmap(void)
{
	FILE *f;
	unsigned int uid = 0, urange = 0, gid = 0, grange = 0;
	char *line = NULL;
	char *uname, *gname;
	size_t len = 0;

	if (!(uname = getuname()))
		return;

	if (!(gname = getgname())) {
		free(uname);
		return;
	}

	f = fopen(subuidfile, "r");
	if (!f) {
		ERROR("Your system is not configured with subuids");
		free(gname);
		free(uname);
		return;
	}
	while (getline(&line, &len, f) != -1) {
		char *p = strchr(line, ':'), *p2;
		if (*line == '#')
			continue;
		if (!p)
			continue;
		*p = '\0';
		p++;
		if (strcmp(line, uname))
			continue;
		p2 = strchr(p, ':');
		if (!p2)
			continue;
		*p2 = '\0';
		p2++;
		if (!*p2)
			continue;
		uid = atoi(p);
		urange = atoi(p2);
	}
	fclose(f);

	f = fopen(subuidfile, "r");
	if (!f) {
		ERROR("Your system is not configured with subgids");
		free(gname);
		free(uname);
		return;
	}
	while (getline(&line, &len, f) != -1) {
		char *p = strchr(line, ':'), *p2;
		if (*line == '#')
			continue;
		if (!p)
			continue;
		*p = '\0';
		p++;
		if (strcmp(line, uname))
			continue;
		p2 = strchr(p, ':');
		if (!p2)
			continue;
		*p2 = '\0';
		p2++;
		if (!*p2)
			continue;
		gid = atoi(p);
		grange = atoi(p2);
	}
	fclose(f);

	free(line);

	if (!urange || !grange) {
		ERROR("You do not have subuids or subgids allocated");
		ERROR("Unprivileged containers require subuids and subgids");
		return;
	}

	ERROR("You must either run as root, or define uid mappings");
	ERROR("To pass uid mappings to lxc-create, you could create");
	ERROR("~/.config/lxc/default.conf:");
	ERROR("lxc.include = %s", LXC_DEFAULT_CONFIG);
	ERROR("lxc.id_map = u 0 %u %u", uid, urange);
	ERROR("lxc.id_map = g 0 %u %u", gid, grange);

	free(gname);
	free(uname);
}
