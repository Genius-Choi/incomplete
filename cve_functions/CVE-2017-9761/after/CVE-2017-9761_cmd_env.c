static int cmd_env(void *data, const char *input) {
	RCore *core = (RCore*)data;
	int ret = true;
	switch (*input) {
	case '?':
		{
		const char* help_msg[] = {
			"Usage:", "%[name[=value]]", "Set each NAME to VALUE in the environment",
			"%", "", "list all environment variables",
			"%", "SHELL", "prints SHELL value",
			"%", "TMPDIR=/tmp", "sets TMPDIR value to \"/tmp\"",
			NULL};
		r_core_cmd_help (core, help_msg);
		}
		break;
	default:
		ret = r_core_cmdf (core, "env %s", input);
	}
	return ret;
}
