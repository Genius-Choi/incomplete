save_directory_hook ()
{
  rl_icppfunc_t *ret;

  if (dircomplete_expand)
    {
      ret = rl_directory_completion_hook;
      rl_directory_completion_hook = (rl_icppfunc_t *)NULL;
    }
  else
    {
      ret = rl_directory_rewrite_hook;
      rl_directory_rewrite_hook = (rl_icppfunc_t *)NULL;
    }

  return ret;
}
