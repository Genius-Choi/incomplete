_destroy_env(char **env)
{
	int i=0;

	if (env) {
		for(i=0; env[i]; i++) {
			xfree(env[i]);
		}
		xfree(env);
	}

	return;
}
