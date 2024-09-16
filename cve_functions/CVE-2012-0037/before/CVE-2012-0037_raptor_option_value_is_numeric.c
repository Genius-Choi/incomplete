raptor_option_value_is_numeric(const raptor_option option)
{
  raptor_option_value_type t = raptor_options_list[option].value_type;
  
  return t == RAPTOR_OPTION_VALUE_TYPE_BOOL ||
         t == RAPTOR_OPTION_VALUE_TYPE_INT;
}
