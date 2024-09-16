set_default_email_from(data_t * data, const char *hostname)
{
	struct passwd *pwd = NULL;
	size_t len;

	if (!hostname || !hostname[0])
		return;

	pwd = getpwuid(getuid());
	if (!pwd)
		return;

	len = strlen(hostname) + strlen(pwd->pw_name) + 2;
	data->email_from = MALLOC(len);
	if (!data->email_from)
		return;

	snprintf(data->email_from, len, "%s@%s", pwd->pw_name, hostname);
}
