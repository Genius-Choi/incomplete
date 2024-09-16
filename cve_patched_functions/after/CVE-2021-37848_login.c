void login(void)
{
	unsigned char passwd[PASSWD_MAX_LENGTH];
	int ret;

	if (!is_passwd_default_enable() && !is_passwd_env_enable())
		return;

	if (logged_in)
		return;

	while (1) {
		printf("Password: ");

		ret = password(passwd, PASSWD_MAX_LENGTH, LOGIN_MODE, login_timeout);
		if (ret < 0)
			run_command(login_fail_command);

		if (ret < 0)
			continue;

		if (check_passwd(passwd, ret) != 1)
			continue;

		logged_in = 1;
		return;
	}
}
