int passwd_env_disable(void)
{
	return unlink(PASSWD_FILE);
}
