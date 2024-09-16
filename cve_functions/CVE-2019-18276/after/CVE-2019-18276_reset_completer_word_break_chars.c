reset_completer_word_break_chars ()
{
  rl_completer_word_break_characters = perform_hostname_completion ? savestring (bash_completer_word_break_characters) : savestring (bash_nohostname_word_break_characters);
}
