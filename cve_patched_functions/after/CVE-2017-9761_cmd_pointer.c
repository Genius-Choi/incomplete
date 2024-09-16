static int cmd_pointer(void *data, const char *input) {
	RCore *core = (RCore*) data;
	int ret = true;
	char *str, *eq;
	while (*input == ' ') input++;
	if (!*input || *input == '?') {
		const char* help_msg[] = {
			"Usage:", "*<addr>[=[0x]value]", "Pointer read/write data/values",
			"*", "entry0=cc", "write trap in entrypoint",
			"*", "entry0+10=0x804800", "write value in delta address",
			"*", "entry0", "read byte at given address",
			"TODO: last command should honor asm.bits", "", "",
			NULL};
		r_core_cmd_help (core, help_msg);
		return ret;
	}
	str = strdup (input);
	eq = strchr (str, '=');
	if (eq) {
		*eq++ = 0;
		if (!strncmp (eq, "0x", 2)) {
			ret = r_core_cmdf (core, "wv %s@%s", eq, str);
		} else {
			ret = r_core_cmdf (core, "wx %s@%s", eq, str);
		}
	} else {
		ret = r_core_cmdf (core, "?v [%s]", input);
	}
	free (str);
	return ret;
}
