static int cmd_ls(void *data, const char *input) {
	if (*input) {
		char *res = r_syscmd_ls (input + 1);
		if (res) {
			r_cons_print (res);
			free (res);
		}
	}
	return 0;
}
