bash_push_line ()
{
  if (push_to_readline)
    {
      rl_insert_text (push_to_readline);
      free (push_to_readline);
      push_to_readline = (char *)NULL;
      rl_startup_hook = old_rl_startup_hook;
    }
  return 0;
}
