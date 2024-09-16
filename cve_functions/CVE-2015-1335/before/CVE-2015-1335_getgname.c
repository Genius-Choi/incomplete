static char *getgname(void)
{
	struct group *result;

	result = getgrgid(getegid());
	if (!result)
		return NULL;

	return strdup(result->gr_name);
}
