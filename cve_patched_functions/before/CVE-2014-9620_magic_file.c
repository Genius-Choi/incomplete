magic_file(struct magic_set *ms, const char *inname)
{
	if (ms == NULL)
		return NULL;
	return file_or_fd(ms, inname, STDIN_FILENO);
}
