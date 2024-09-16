make_pidfile_name(const char* start, const char* instance, const char* extn)
{
	size_t len;
	char *name;

	len = strlen(start) + 1;
	if (instance)
		len += strlen(instance) + 1;
	if (extn)
		len += strlen(extn);

	name = MALLOC(len);
	if (!name) {
		log_message(LOG_INFO, "Unable to make pidfile name for %s", start);
		return NULL;
	}

	strcpy(name, start);
	if (instance) {
		strcat(name, "_");
		strcat(name, instance);
	}
	if (extn)
		strcat(name, extn);

	return name;
}
