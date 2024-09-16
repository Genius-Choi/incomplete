drop_privs (void)
{
  if (!is_privileged)
    return;

  /* Drop root uid */
  if (setuid (opt_sandbox_uid) < 0)
    die_with_error ("unable to drop root uid");

  drop_all_caps ();
}
