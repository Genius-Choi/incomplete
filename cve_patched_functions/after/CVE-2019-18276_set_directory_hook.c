set_directory_hook ()
{
  if (dircomplete_expand)
    {
      rl_directory_completion_hook = bash_directory_completion_hook;
      rl_directory_rewrite_hook = (rl_icppfunc_t *)0;
    }
  else
    {
      rl_directory_rewrite_hook = bash_directory_completion_hook;
      rl_directory_completion_hook = (rl_icppfunc_t *)0;
    }
}
