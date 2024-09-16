raptor_object_options_clear(raptor_object_options* options)
{
  int i;
  
  for(i = 0; i <= RAPTOR_OPTION_LAST; i++) {
    if(raptor_option_value_is_numeric((raptor_option)i))
      continue;

    if(options->options[i].string)
      RAPTOR_FREE(char*, options->options[i].string);
  }
}
