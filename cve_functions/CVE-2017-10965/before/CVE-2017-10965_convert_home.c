char *convert_home(const char *path)
{
	const char *home;

	if (*path == '~' && (*(path+1) == '/' || *(path+1) == '\0')) {
		home = g_get_home_dir();
		if (home == NULL)
			home = ".";

		return g_strconcat(home, path+1, NULL);
	} else {
		return g_strdup(path);
	}
}
