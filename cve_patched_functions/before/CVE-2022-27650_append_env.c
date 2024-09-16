append_env (const char *arg)
{
  exec_options.env = realloc (exec_options.env, (exec_options.env_size + 2) * sizeof (*exec_options.env));
  if (exec_options.env == NULL)
    error (EXIT_FAILURE, errno, "cannot allocate memory");
  exec_options.env[exec_options.env_size + 1] = NULL;
  exec_options.env[exec_options.env_size] = xstrdup (arg);
  exec_options.env_size++;
}
