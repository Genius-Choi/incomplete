static int login_global_init(void)
{
	login_fail_command = xstrdup("boot");

	globalvar_add_simple_int("login.timeout", &login_timeout, "%d");
	globalvar_add_simple_string("login.fail_command", &login_fail_command);

	return 0;
}
