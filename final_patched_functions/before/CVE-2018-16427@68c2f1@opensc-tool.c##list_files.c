static int list_files(void)
{
	sc_path_t path;
	int r;

	sc_format_path("3F00", &path);
	r = enum_dir(path, 0);
	return r;
}
