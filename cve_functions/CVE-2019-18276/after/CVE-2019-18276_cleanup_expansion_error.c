cleanup_expansion_error ()
{
  char *to_free;
#if defined (BANG_HISTORY)
  int old_verify;

  old_verify = hist_verify;
  hist_verify = 0;
#endif

  fprintf (rl_outstream, "\r\n");
  to_free = pre_process_line (rl_line_buffer, 1, 0);
#if defined (BANG_HISTORY)
  hist_verify = old_verify;
#endif
  if (to_free != rl_line_buffer)
    FREE (to_free);
  putc ('\r', rl_outstream);
  rl_forced_update_display ();
}
