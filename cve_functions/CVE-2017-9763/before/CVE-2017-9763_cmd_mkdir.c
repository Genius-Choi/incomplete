static int cmd_mkdir(void *data, const char *input) {
	char *res = r_syscmd_mkdir (input);
	if (res) {
		r_cons_print (res);
		free (res);
	}
	return 0;
}
