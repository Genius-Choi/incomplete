static bool in_comma_list(const char *inword, const char *cgroup_use)
{
	char *e;
	size_t inlen = strlen(inword), len;

	do {
		e = strchr(cgroup_use, ',');
		len = e ? e - cgroup_use : strlen(cgroup_use);
		if (len == inlen && strncmp(inword, cgroup_use, len) == 0)
			return true;
		cgroup_use = e + 1;
	} while (e);

	return false;
}
