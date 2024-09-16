static const char *mlsd_type(char *name, int mode)
{
	if (!strcmp(name, "."))
		return "cdir";
	if (!strcmp(name, ".."))
		return "pdir";

	return S_ISDIR(mode) ? "dir" : "file";
}
