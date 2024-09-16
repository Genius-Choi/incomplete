init_groups (const struct passwd *pw, gid_t *groups, size_t num_groups)
{
  int retval;

  errno = 0;

  if (num_groups)
    retval = setgroups (num_groups, groups);
  else
    retval = initgroups (pw->pw_name, pw->pw_gid);

  if (retval == -1)
    {
      cleanup_pam (PAM_ABORT);
      err (EXIT_FAILURE, _("cannot set groups"));
    }
  endgrent ();

  retval = pam_setcred (pamh, PAM_ESTABLISH_CRED);
  if (is_pam_failure(retval))
    errx (EXIT_FAILURE, "%s", pam_strerror (pamh, retval));
  else
    _pam_cred_established = 1;
}
