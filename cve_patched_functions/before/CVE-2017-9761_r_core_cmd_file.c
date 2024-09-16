R_API int r_core_cmd_file(RCore *core, const char *file) {
	char *data, *odata;
	data = r_file_abspath (file);
	if (!data) return false;
	odata = r_file_slurp (data, NULL);
	free (data);
	if (!odata) return false;
	if (!r_core_cmd_lines (core, odata)) {
		eprintf ("Failed to run script '%s'\n", file);
		free (odata);
		return false;
	}
	free (odata);
	return true;
}
