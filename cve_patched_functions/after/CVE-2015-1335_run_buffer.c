static int run_buffer(char *buffer)
{
	struct lxc_popen_FILE *f;
	char *output;
	int ret;

	f = lxc_popen(buffer);
	if (!f) {
		SYSERROR("popen failed");
		return -1;
	}

	output = malloc(LXC_LOG_BUFFER_SIZE);
	if (!output) {
		ERROR("failed to allocate memory for script output");
		lxc_pclose(f);
		return -1;
	}

	while(fgets(output, LXC_LOG_BUFFER_SIZE, f->f))
		DEBUG("script output: %s", output);

	free(output);

	ret = lxc_pclose(f);
	if (ret == -1) {
		SYSERROR("Script exited on error");
		return -1;
	} else if (WIFEXITED(ret) && WEXITSTATUS(ret) != 0) {
		ERROR("Script exited with status %d", WEXITSTATUS(ret));
		return -1;
	} else if (WIFSIGNALED(ret)) {
		ERROR("Script terminated by signal %d (%s)", WTERMSIG(ret),
		      strsignal(WTERMSIG(ret)));
		return -1;
	}

	return 0;
}
