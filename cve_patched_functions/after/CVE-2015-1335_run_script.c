static int run_script(const char *name, const char *section,
		      const char *script, ...)
{
	int ret;
	char *buffer, *p;
	size_t size = 0;
	va_list ap;

	INFO("Executing script '%s' for container '%s', config section '%s'",
	     script, name, section);

	va_start(ap, script);
	while ((p = va_arg(ap, char *)))
		size += strlen(p) + 1;
	va_end(ap);

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

	ret = snprintf(buffer, size, "%s %s %s", script, name, section);
	if (ret < 0 || ret >= size) {
		ERROR("Script name too long");
		return -1;
	}

	va_start(ap, script);
	while ((p = va_arg(ap, char *))) {
		int len = size-ret;
		int rc;
		rc = snprintf(buffer + ret, len, " %s", p);
		if (rc < 0 || rc >= len) {
			ERROR("Script args too long");
			return -1;
		}
		ret += rc;
	}
	va_end(ap);

	return run_buffer(buffer);
}
