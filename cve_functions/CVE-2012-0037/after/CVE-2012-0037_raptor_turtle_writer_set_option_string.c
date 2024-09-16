raptor_turtle_writer_set_option_string(raptor_turtle_writer *turtle_writer, 
                                        raptor_option option, 
                                        const unsigned char *value)
{
  if(!value ||
     !raptor_option_is_valid_for_area(option, RAPTOR_OPTION_AREA_TURTLE_WRITER))
    return 1;

  if(raptor_option_value_is_numeric(option))
    return raptor_turtle_writer_set_option(turtle_writer, option, 
                                            atoi((const char*)value));

  return 1;
}
