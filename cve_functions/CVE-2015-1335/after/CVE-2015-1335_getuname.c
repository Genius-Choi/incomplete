static char* getuname(void)
{
	struct passwd *result;

	result = getpwuid(geteuid());
	if (!result)
		return NULL;

	return strdup(result->pw_name);
}
