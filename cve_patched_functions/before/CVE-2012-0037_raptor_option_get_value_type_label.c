raptor_option_get_value_type_label(const raptor_option_value_type type)
{
  if(type > RAPTOR_OPTION_VALUE_TYPE_LAST)
    return NULL;
  return raptor_option_value_type_labels[type];
}
