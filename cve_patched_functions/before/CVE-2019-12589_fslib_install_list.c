void fslib_install_list(const char *lib_list) {
	assert(lib_list);
	if (arg_debug || arg_debug_private_lib)
		printf("    fslib_install_list  %s\n", lib_list);

	char *dlist = strdup(lib_list);
	if (!dlist)
		errExit("strdup");

	char *ptr = strtok(dlist, ",");
	if (!ptr) {
		fprintf(stderr, "Error: invalid private-lib argument\n");
		exit(1);
	}
	install_list_entry(ptr);

	while ((ptr = strtok(NULL, ",")) != NULL)
		install_list_entry(ptr);
	free(dlist);
	fs_logger_print();
}
