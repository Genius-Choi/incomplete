raptor_option_is_valid_for_area(const raptor_option option,
                                raptor_option_area area)
{
  if(option > RAPTOR_OPTION_LAST)
    return 0;
  return (raptor_options_list[option].area & area) != 0;
}
