bashline_reset ()
{
  tilde_initialize ();
  rl_attempted_completion_function = attempt_shell_completion;
  rl_completion_entry_function = NULL;
  rl_ignore_some_completions_function = filename_completion_ignore;
  rl_filename_quote_characters = default_filename_quote_characters;
  set_filename_bstab (rl_filename_quote_characters);

  set_directory_hook ();
  rl_filename_stat_hook = bash_filename_stat_hook;

  bashline_reset_event_hook ();

  rl_sort_completion_matches = 1;
}
