static int run_script_argv(const char *name, const char *section,
		      const char *script, const char *hook, const char *lxcpath,
		      char **argsin)
{
	int ret, i;
	char *buffer;
	size_t size = 0;

	INFO("Executing script '%s' for container '%s', config section '%s'",
	     script, name, section);

	for (i=0; argsin && argsin[i]; i++)
		size += strlen(argsin[i]) + 1;

	size += strlen(hook) + 1;

	size += strlen(script);
	size += strlen(name);
	size += strlen(section);
	size += 3;

	if (size > INT_MAX)
		return -1;

	buffer = alloca(size);
	if (!buffer) {
		ERROR("failed to allocate memory");
		return -1;
	}

	ret = snprintf(buffer, size, "%s %s %s %s", script, name, section, hook);
	if (ret < 0 || ret >= size) {
		ERROR("Script name too long");
		return -1;
	}

	for (i=0; argsin && argsin[i]; i++) {
		int len = size-ret;
		int rc;
		rc = snprintf(buffer + ret, len, " %s", argsin[i]);
		if (rc < 0 || rc >= len) {
			ERROR("Script args too long");
			return -1;
		}
		ret += rc;
	}

	return run_buffer(buffer);
}
