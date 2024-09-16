make_oci_process_user (const char *userspec)
{
  runtime_spec_schema_config_schema_process_user *u;
  char *endptr = NULL;

  if (userspec == NULL)
    return NULL;

  u = xmalloc0 (sizeof (runtime_spec_schema_config_schema_process_user));
  errno = 0;
  u->uid = strtol (userspec, &endptr, 10);
  if (errno == ERANGE)
    libcrun_fail_with_error (0, "invalid UID specified");
  if (*endptr == '\0')
    return u;
  if (*endptr != ':')
    libcrun_fail_with_error (0, "invalid USERSPEC specified");

  errno = 0;
  u->gid = strtol (endptr + 1, &endptr, 10);
  if (errno == ERANGE)
    libcrun_fail_with_error (0, "invalid GID specified");
  if (*endptr != '\0')
    libcrun_fail_with_error (0, "invalid USERSPEC specified");

  return u;
}
