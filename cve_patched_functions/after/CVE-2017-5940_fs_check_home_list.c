void fs_check_home_list(void) {
	if (strstr(cfg.home_private_keep, "..")) {
		fprintf(stderr, "Error: invalid private-home list\n");
		exit(1);
	}

	char *dlist = strdup(cfg.home_private_keep);
	if (!dlist)
		errExit("strdup");

	char *ptr = strtok(dlist, ",");
	char *tmp = check_dir_or_file(ptr);
	free(tmp);

	while ((ptr = strtok(NULL, ",")) != NULL) {
		tmp = check_dir_or_file(ptr);
		free(tmp);
	}

	free(dlist);
}
