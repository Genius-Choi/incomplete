parse_sharetab(sa_handle_impl_t impl_handle) {
	FILE *fp;
	char line[512];
	char *eol, *pathname, *resource, *fstype, *options, *description;

	fp = fopen("/etc/dfs/sharetab", "r");

	if (fp == NULL)
		return;

	while (fgets(line, sizeof (line), fp) != NULL) {
		eol = line + strlen(line) - 1;

		while (eol >= line) {
			if (*eol != '\r' && *eol != '\n')
				break;

			*eol = '\0';
			eol--;
		}

		pathname = line;

		if ((resource = strchr(pathname, '\t')) == NULL)
			continue;

		*resource = '\0';
		resource++;

		if ((fstype = strchr(resource, '\t')) == NULL)
			continue;

		*fstype = '\0';
		fstype++;

		if ((options = strchr(fstype, '\t')) == NULL)
			continue;

		*options = '\0';
		options++;

		if ((description = strchr(fstype, '\t')) != NULL) {
			*description = '\0';
			description++;
		}

		if (strcmp(resource, "-") == 0)
			resource = NULL;

		(void) process_share(impl_handle, NULL, pathname, resource,
		    fstype, options, description, NULL, B_TRUE);
	}

	fclose(fp);
}
