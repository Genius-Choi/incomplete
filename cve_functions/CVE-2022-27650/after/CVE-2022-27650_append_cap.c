append_cap (const char *arg)
{
  exec_options.cap = realloc (exec_options.cap, (exec_options.cap_size + 2) * sizeof (*exec_options.cap));
  if (exec_options.cap == NULL)
    error (EXIT_FAILURE, errno, "cannot allocate memory");
  exec_options.cap[exec_options.cap_size + 1] = NULL;
  exec_options.cap[exec_options.cap_size] = xstrdup (arg);
  exec_options.cap_size++;
}
